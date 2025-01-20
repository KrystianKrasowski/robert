#include "gpio.h"
#include <avr/io.h>
#include <stdint.h>

typedef struct gpio_definition
{
    uint8_t volatile *ddrx;
    uint8_t volatile *portx;
    uint8_t  bit;
} gpio_definition_t;

static void
init_gpio_object(gpio_t *self);

static void
init_gpio_peripheral(gpio_t *self);

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
gpio_init(gpio_t *self)
{
    init_gpio_object(self);
    init_gpio_peripheral(self);
}

void
gpio_set_state(gpio_t *self, gpio_state_t const state)
{
    gpio_definition_t definition = gpio[self->pin];

    if (state == GPIO_STATE_HIGH)
    {
        *definition.portx |= (1 << definition.bit);
    }
    else
    {
        *definition.portx &= ~(1 << definition.bit);
    }

    self->state = state;
}

static void
init_gpio_object(gpio_t *self)
{
    self->mode = GPIO_MODE_OUTPUT;
    self->state = GPIO_STATE_LOW;
}

static void
init_gpio_peripheral(gpio_t *self)
{
    gpio_definition_t definition = gpio[self->pin];

    if (self->mode == GPIO_MODE_OUTPUT)
    {
        *definition.ddrx |= (1 << definition.bit);
    }
    else
    {
        *definition.ddrx &= ~(1 << definition.bit);
    }
}