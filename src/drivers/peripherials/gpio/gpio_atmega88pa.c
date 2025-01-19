#include "gpio.h"
#include <avr/io.h>
#include <stdint.h>

static uint8_t ddrb_buffer  = 0;
static uint8_t ddrc_buffer  = 0;
static uint8_t ddrd_buffer  = 0;
static uint8_t portb_buffer = 0;
static uint8_t portc_buffer = 0;
static uint8_t portd_buffer = 0;

typedef struct gpio_definition
{
    uint8_t *ddrx;
    uint8_t *portx;
    uint8_t  bit;
} gpio_definition_t;

static gpio_definition_t gpio[9] = {
    [GPIO_L293_LEFT_FRONT_A1]   = {&ddrc_buffer, &portc_buffer, 3},
    [GPIO_L293_LEFT_FRONT_A2]   = {&ddrc_buffer, &portc_buffer, 2},
    [GPIO_L293_RIGHT_FRONT_A1]  = {&ddrd_buffer, &portd_buffer, 0},
    [GPIO_L293_RIGHT_FRONT_A2]  = {&ddrd_buffer, &portd_buffer, 1},
    [GPIO_L293_LEFT_REAR_A1]    = {&ddrc_buffer, &portc_buffer, 5},
    [GPIO_L293_LEFT_REAR_A2]    = {&ddrc_buffer, &portc_buffer, 4},
    [GPIO_L293_RIGHT_REAR_A1]   = {&ddrd_buffer, &portd_buffer, 2},
    [GPIO_L293_RIGHT_REAR_A2]   = {&ddrd_buffer, &portd_buffer, 3},
    [GPIO_DUALSHOCK2_ATTENTION] = {&ddrb_buffer, &portb_buffer, 1},
};

void
gpio_init(gpio_pin_t pin)
{
    *gpio[pin].ddrx |= (1 << gpio[pin].bit);
}

void
gpio_apply_modes(void)
{
    DDRB = ddrb_buffer;
    DDRC = ddrc_buffer;
    DDRD = ddrd_buffer;
}

void
gpio_set(gpio_pin_t pin, gpio_state_t state)
{
    if (state == GPIO_STATE_HIGH)
    {
        *gpio[pin].portx |= (1 << gpio[pin].bit);
    }
    else
    {
        *gpio[pin].portx &= ~(1 << gpio[pin].bit);
    }
}

void
gpio_apply_states(void)
{
    PORTB = portb_buffer;
    PORTC = portc_buffer;
    PORTD = portd_buffer;
}

void
gpio_reset_modes(void)
{
    ddrb_buffer = 0;
    ddrc_buffer = 0;
    ddrd_buffer = 0;
    gpio_apply_modes();
}

void
gpio_reset_states(void)
{
    portb_buffer = 0;
    portc_buffer = 0;
    portd_buffer = 0;
    gpio_apply_states();
}
