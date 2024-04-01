#include "dualshock2.h"
#include <avrhal/gpio.h>
#include <avrhal/spi.h>
#include <avrhal/timer1.h>
#include <avrhal/timer1_ctc.h>
#include <avrhal/timer1_interrupts.h>

typedef struct
{
    uint8_t start         : 1;
    uint8_t wait          : 1;
    uint8_t transmit      : 1;
    uint8_t finish        : 1;
    uint8_t command_index : 4;
} ds2_communication_t;

static void
ds2_state_update(void);

static hal_gpio_t ds2_attention = {
    .pin       = HAL_GPIO_PB1,
    .direction = HAL_GPIO_OUTPUT,
};

static const hal_spi_t spi = {
    .interrupts     = 1,
    .order          = HAL_SPI_BIT_ORDER_LSB_FIRST,
    .clock_polarity = HAL_SPI_CLOCK_POLARITY_FALLING_RISING,
    .clock_phase    = HAL_SPI_CLOCK_PHASE_SETUP_SAMPLE,
    .prescaller     = HAL_SPI_PRESCALLER_32,
};

static const hal_timer1_ctc_t timer1_ctc = {
    .resolution       = 16000,
    .output_compare_b = 200,
};

static const hal_timer1_interrupts_t timer1_interrupts = {
    .output_compare_a = 1,
    .output_compare_b = 1,
};

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
    hal_gpio_init(&ds2_attention);
    hal_gpio_write(&ds2_attention, HAL_GPIO_HIGH);
    hal_timer1_ctc_init(&timer1_ctc);
    hal_timer1_interrupts_init(&timer1_interrupts);
    hal_spi_master_init(&spi);
    hal_timer1_run(HAL_TIMER_PRESCALLER_8);
}

uint16_t
dualshock2_read(void)
{
    if (ds2_communication.start)
    {
        ds2_communication.start = 0;
        hal_gpio_write(&ds2_attention, HAL_GPIO_LOW);
    }

    if (ds2_communication.transmit)
    {
        ds2_communication.transmit = 0;
        hal_spi_master_transmit(
            command_sequence[ds2_communication.command_index]);
    }

    if (ds2_communication.finish)
    {
        ds2_communication.finish = 0;
        hal_gpio_write(&ds2_attention, HAL_GPIO_HIGH);
        ds2_communication.command_index = 0;
        ds2_state_update();
    }

    return last_state;
}

void
hal_spi_transfer_complete_isr(const uint8_t chr)
{
    response[ds2_communication.command_index++] = chr;

    if (ds2_communication.command_index <= 8)
    {
        ds2_communication.transmit = 1;
    }
    else
    {
        ds2_communication.finish = 1;
    }
}

void
hal_timer1_output_compare_a_isr(void)
{
    ds2_communication.start = 1;
    ds2_communication.wait  = 1;
}

void
hal_timer1_output_compare_b_isr(void)
{
    if (ds2_communication.wait)
    {
        ds2_communication.wait     = 0;
        ds2_communication.transmit = 1;
    }
}

static void
ds2_state_update(void)
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
