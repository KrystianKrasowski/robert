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
    GPIO_STATE_HIGH,
    GPIO_STATE_LOW,
} gpio_state_t;

void
gpio_init_output(gpio_pin_t pin);

void
gpio_apply_modes(void);

void
gpio_set_output(gpio_pin_t pin, gpio_state_t state);

void
gpio_apply_states(void);

void
gpio_reset_modes(void);

void
gpio_reset_states(void);

#endif