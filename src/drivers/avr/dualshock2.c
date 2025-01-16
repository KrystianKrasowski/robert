#include "drivers/dualshock2.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define DS2_ATTENTION_DDR      DDRB
#define DS2_ATTENTION_PORT     PORTB
#define DS2_ATTENTION_DDR_BIT  DDB1
#define DS2_ATTENTION_PORT_BIT PORTB1

static void
dualshock2_init_attention_pin(void);

static void
dualshock2_init_timer1(void);

static void
dualshock2_init_spi_master(void);

static void
dualshock2_spi_transmit_next();

static void
dualshock2_state_update(void);

typedef struct
{
    uint8_t start         : 1;
    uint8_t wait          : 1;
    uint8_t transmit      : 1;
    uint8_t finish        : 1;
    uint8_t command_index : 4;
} ds2_communication_t;

static const uint8_t command_sequence[9] = {
    0x01,
    0x42,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};

static volatile uint16_t last_state = DS2_NONE;

static volatile ds2_communication_t ds2_communication = {
    .start         = 0,
    .wait          = 0,
    .transmit      = 0,
    .finish        = 0,
    .command_index = 0,
};

static volatile uint8_t response[9] = {0};

void
dualshock2_init(void)
{
    dualshock2_init_attention_pin();
    dualshock2_init_spi_master();
    dualshock2_init_timer1();
}

static void
dualshock2_init_attention_pin(void)
{
    DS2_ATTENTION_DDR |= (1 << DS2_ATTENTION_DDR_BIT);
    DS2_ATTENTION_PORT |= (1 << DS2_ATTENTION_PORT_BIT);
}

static void
dualshock2_init_spi_master(void)
{
    // slave select is configured as input with pull-up due to securing master
    // mode
    SS_DDR &= ~(1 << SS_BIT);
    SS_PORT |= (1 << SS_BIT);

    // configure necessary outputs for master mode - MOSI and clock
    MOSI_DDR |= (1 << MOSI_BIT);
    SCK_DDR |= (1 << SCK_BIT);

    // configure SPCR value
    uint8_t spcr_value = 0;
    uint8_t spsr_value = 0;

    // configure SPI interface in master mode
    spcr_value |= (1 << SPE) | (1 << MSTR);

    // configure SPI interrupts
    spcr_value |= (1 << SPIE);

    // configure lsb first order
    spcr_value |= (1 << DORD);

    // configure clock polarity as falling-rising
    spcr_value |= (1 << CPOL);

    // configure clock phase as setup-sample
    spcr_value |= (1 << CPHA);

    // configure spi clock speed prescaller to 32
    spcr_value &= ~(1 << SPR0);
    spcr_value |= (1 << SPR1);
    spsr_value |= (1 << SPI2X);

    // write to SPCR and SPSR as one operation due to performence optimaization
    SPCR = spcr_value;
    SPSR = spsr_value;
}

static void
dualshock2_init_timer1(void)
{
    // configure timer1 in CTC mode and 8 prescaller
    TCCR1B |= (1 << WGM12) | (1 << CS11);

    // configure controller state read each 16 ms
    OCR1A = 16000;

    // configure controller read start delay for 200 us
    OCR1B = 200;

    // configure timer1 with interrupts on both channels a and b
    TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B);
}

ISR(TIMER1_COMPA_vect)
{
    dualshock2_handle_request_prepare_isr();
}

void
dualshock2_handle_request_prepare_isr(void)
{
    ds2_communication.start = 1;
    ds2_communication.wait  = 1;
}

ISR(TIMER1_COMPB_vect)
{
    dualshock2_handle_request_transmit_isr();
}

void
dualshock2_handle_request_transmit_isr(void)
{
    if (ds2_communication.wait)
    {
        ds2_communication.wait     = 0;
        ds2_communication.transmit = 1;
    }
}

ISR(SPI_STC_vect)
{
    dualshock2_handle_response_isr(SPDR);
}

void
dualshock2_handle_response_isr(const uint8_t response_byte)
{
    response[ds2_communication.command_index++] = response_byte;

    if (ds2_communication.command_index <= 8)
    {
        ds2_communication.transmit = 1;
    }
    else
    {
        ds2_communication.finish = 1;
    }
}

uint16_t
dualshock2_read(void)
{
    if (ds2_communication.start)
    {
        ds2_communication.start = 0;
        DS2_ATTENTION_PORT &= ~(1 << DS2_ATTENTION_PORT_BIT);
    }

    if (ds2_communication.transmit)
    {
        ds2_communication.transmit = 0;
        dualshock2_spi_transmit_next();
    }

    if (ds2_communication.finish)
    {
        ds2_communication.finish = 0;
        DS2_ATTENTION_PORT |= (1 << DS2_ATTENTION_DDR_BIT);
        ds2_communication.command_index = 0;
        dualshock2_state_update();
    }

    return last_state;
}

static void
dualshock2_spi_transmit_next(void)
{
    SPDR = command_sequence[ds2_communication.command_index];
}

static void
dualshock2_state_update(void)
{
    if (response[0] != 0xff || (response[1] != 0x41 && response[1] != 0x73) ||
        response[2] != 0x5a)
    {
        last_state = DS2_NONE;
    }
    else
    {
        last_state = ~(((uint16_t)response[4] << 8) | response[3]);
    }
}