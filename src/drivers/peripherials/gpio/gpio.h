#ifndef _GPIO_H
#define _GPIO_H

#include <stdbool.h>

typedef enum
{
    GPIO_L293_LEFT_FRONT_A1,
    GPIO_L293_LEFT_FRONT_A2,
    GPIO_L293_RIGHT_FRONT_A1,
    GPIO_L293_RIGHT_FRONT_A2,
    GPIO_L293_LEFT_REAR_A1,
    GPIO_L293_LEFT_REAR_A2,
    GPIO_L293_RIGHT_REAR_A1,
    GPIO_L293_RIGHT_REAR_A2,
    GPIO_DUALSHOCK2_ATTENTION,
} gpio_pin_t;

typedef enum
{
    GPIO_MODE_OUTPUT,
} gpio_mode_t;

typedef enum
{
    GPIO_STATE_HIGH,
    GPIO_STATE_LOW,
} gpio_state_t;

typedef struct gpio
{
    gpio_pin_t const pin;
    gpio_mode_t      mode;
    gpio_state_t     state;
} gpio_t;

void
gpio_init(gpio_t *self);

void
gpio_set_state(gpio_t *self, gpio_state_t const state);

#endif