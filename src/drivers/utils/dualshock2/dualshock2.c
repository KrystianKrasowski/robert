#include "dualshock2.h"
#include "gpio.h"
#include "spi.h"
#include "timer.h"

typedef struct
{
    uint8_t start    : 1;
    uint8_t wait     : 1;
    uint8_t transmit : 1;
    uint8_t busy     : 1;
    uint8_t finish   : 1;
} ds2_communication_t;

typedef enum
{
    STANDBY,
    ATTENTION,
    TRANSMIT,
    CHECK_RESPONSE,
    FINISH,
} ds2_state_t;

// TODO: Rename those variables:
// last_state - last response
// ds2_communication - ds2_communication_state
static uint16_t last_state = DS2_NONE;

volatile ds2_communication_t ds2_communication = {
    .start    = 0,
    .wait     = 0,
    .transmit = 0,
    .busy     = 0,
    .finish   = 0,
};

uint8_t command_sequence[9] = {
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

static uint8_t response[9] = {0};

static volatile ds2_state_t ds2_state = STANDBY;

static gpio_t attention;

static void
dualshock2_state_update(void);

void
dualshock2_init(void)
{
    attention = gpio_create(GPIO_DUALSHOCK2_ATTENTION);
    gpio_set_state(&attention, GPIO_STATE_HIGH);
    spi_init_master();
    timer_init();
}

uint16_t
dualshock2_read(void)
{
    if (ds2_state == ATTENTION)
    {
        gpio_set_state(&attention, GPIO_STATE_LOW);
        ds2_state = STANDBY;
    }

    if (ds2_state == TRANSMIT)
    {
        spi_transmit(command_sequence, 9);
        ds2_state = CHECK_RESPONSE;
    }

    if (ds2_state == CHECK_RESPONSE)
    {
        bool response_ready = spi_receive(response, 9);

        if (response_ready)
        {
            ds2_state = FINISH;
        }
    }

    if (ds2_state == FINISH)
    {
        gpio_set_state(&attention, GPIO_STATE_HIGH);
        ds2_state = STANDBY;
        dualshock2_state_update();
    }

    return last_state;
}

// uint16_t
// dualshock2_read(void)
// {
//     if (ds2_communication.start)
//     {
//         ds2_communication.start = 0;
//         gpio_set_state(&attention, GPIO_STATE_LOW);
//     }

//     if (ds2_communication.transmit)
//     {
//         if (ds2_communication.busy == 0)
//         {
//             spi_transmit(command_sequence, 9);
//             ds2_communication.busy = 1;
//         }
//         bool received = spi_receive(response, 9);
//         if (received)
//         {
//             ds2_communication.transmit = 0;
//             ds2_communication.finish   = 1;
//             ds2_communication.busy     = 0;
//         }
//     }

//     if (ds2_communication.finish)
//     {
//         ds2_communication.finish = 0;
//         gpio_set_state(&attention, GPIO_STATE_HIGH);
//         dualshock2_state_update();
//     }

//     return last_state;
// }

void
timer_compare_a_match_isr(void)
{
    if (ds2_state == STANDBY)
    {
        ds2_state = ATTENTION;
    }
    // ds2_communication.start = 1;
    // ds2_communication.wait  = 1;
}

void
timer_compare_b_match_isr(void)
{
    if (ds2_state == STANDBY)
    {
        ds2_state = TRANSMIT;
    }
    // if (ds2_communication.wait)
    // {
    //     ds2_communication.wait     = 0;
    //     ds2_communication.transmit = 1;
    // }
}

// void
// spi_on_response_received_isr(uint8_t const resposne_byte)
// {
//     response[ds2_communication.command_index++] = resposne_byte;

//     if (ds2_communication.command_index <= 8)
//     {
//         ds2_communication.transmit = 1;
//     }
//     else
//     {
//         ds2_communication.finish = 1;
//     }
// }

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