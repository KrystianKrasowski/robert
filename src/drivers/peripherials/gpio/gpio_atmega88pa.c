#include "gpio.h"
#include <avr/io.h>
#include <stdint.h>

typedef struct gpio_definition
{
    uint8_t volatile *ddrx;
    uint8_t volatile *portx;
    uint8_t  bit;
} gpio_definition_t;

static gpio_definition_t gpio[9] = {
    [GPIO_L293_LEFT_FRONT_A1]   = {&DDRC, &PORTC, 3},
    [GPIO_L293_LEFT_FRONT_A2]   = {&DDRC, &PORTC, 2},
    [GPIO_L293_RIGHT_FRONT_A1]  = {&DDRD, &PORTD, 0},
    [GPIO_L293_RIGHT_FRONT_A2]  = {&DDRD, &PORTD, 1},
    [GPIO_L293_LEFT_REAR_A1]    = {&DDRC, &PORTC, 5},
    [GPIO_L293_LEFT_REAR_A2]    = {&DDRC, &PORTC, 4},
    [GPIO_L293_RIGHT_REAR_A1]   = {&DDRD, &PORTD, 2},
    [GPIO_L293_RIGHT_REAR_A2]   = {&DDRD, &PORTD, 3},
    [GPIO_DUALSHOCK2_ATTENTION] = {&DDRB, &PORTB, 1},
};

void
gpio_init_output(gpio_pin_t pin)
{
    *gpio[pin].ddrx |= (1 << gpio[pin].bit);
}

void
gpio_apply_modes(void)
{

}

void
gpio_set_output(gpio_pin_t pin, gpio_state_t state)
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

}

void
gpio_reset_modes(void)
{

    gpio_apply_modes();
}

void
gpio_reset_states(void)
{

    gpio_apply_states();
}
