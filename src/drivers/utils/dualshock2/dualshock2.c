#include "dualshock2.h"
#include "gpio.h"
#include "spi.h"
#include "timer.h"

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

// TODO: Rename those variables:
// last_state - last response
// ds2_communication - ds2_communication_state 
static volatile uint16_t last_state = DS2_NONE;

static volatile ds2_communication_t ds2_communication = {
    .start         = 0,
    .wait          = 0,
    .transmit      = 0,
    .finish        = 0,
    .command_index = 0,
};

static volatile uint8_t response[9] = {0};

static void
dualshock2_spi_transmit_next();

static void
dualshock2_state_update(void);

void
dualshock2_init(void)
{
    gpio_init_output(GPIO_DUALSHOCK2_ATTENTION);
    gpio_apply_modes();
    gpio_set_output(GPIO_DUALSHOCK2_ATTENTION, GPIO_STATE_HIGH);
    gpio_apply_states();

    spi_init_master();
    timer_init();
}

uint16_t
dualshock2_read(void)
{
    if (ds2_communication.start)
    {
        ds2_communication.start = 0;
        gpio_set_output(GPIO_DUALSHOCK2_ATTENTION, GPIO_STATE_LOW);
        gpio_apply_states();
    }

    if (ds2_communication.transmit)
    {
        ds2_communication.transmit = 0;
        dualshock2_spi_transmit_next();
    }

    if (ds2_communication.finish)
    {
        ds2_communication.finish = 0;
        gpio_set_output(GPIO_DUALSHOCK2_ATTENTION, GPIO_STATE_HIGH);
        gpio_apply_states();
        ds2_communication.command_index = 0;
        dualshock2_state_update();
    }

    return last_state;
}

void
timer_compare_a_match_isr(void)
{
    ds2_communication.start = 1;
    ds2_communication.wait  = 1;
}

void
timer_compare_b_match_isr(void)
{
    if (ds2_communication.wait)
    {
        ds2_communication.wait     = 0;
        ds2_communication.transmit = 1;
    }
}

void
spi_on_response_received_isr(uint8_t resposne_byte)
{
    response[ds2_communication.command_index++] = resposne_byte;

    if (ds2_communication.command_index <= 8)
    {
        ds2_communication.transmit = 1;
    }
    else
    {
        ds2_communication.finish = 1;
    }
}

static void
dualshock2_spi_transmit_next(void)
{
    spi_transmit(command_sequence[ds2_communication.command_index]);
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