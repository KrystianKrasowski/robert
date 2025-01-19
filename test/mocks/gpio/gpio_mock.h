#ifndef _GPIO_MOCK_H
#define _GPIO_MOCK_H

#include "gpio.h"
#include <stdbool.h>

bool
gpio_verify_output_initialized(gpio_pin_t pin);

bool
gpio_verify_modes_applied(void);

bool
gpio_verify_output_set(gpio_pin_t pin, gpio_state_t state);

bool
gpio_verify_states_applied(void);

#endif