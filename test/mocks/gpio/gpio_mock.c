#include "gpio_mock.h"

#define GPIO_SIZE 9

static bool initialized_outputs[GPIO_SIZE] = {
    [GPIO_L293_LEFT_FRONT_A1]   = false,
    [GPIO_L293_LEFT_FRONT_A2]   = false,
    [GPIO_L293_RIGHT_FRONT_A1]  = false,
    [GPIO_L293_RIGHT_FRONT_A2]  = false,
    [GPIO_L293_LEFT_REAR_A1]    = false,
    [GPIO_L293_LEFT_REAR_A2]    = false,
    [GPIO_L293_RIGHT_REAR_A1]   = false,
    [GPIO_L293_RIGHT_REAR_A2]   = false,
    [GPIO_DUALSHOCK2_ATTENTION] = false,
};

static gpio_state_t pin_states[GPIO_SIZE] = {
    [GPIO_L293_LEFT_FRONT_A1]   = GPIO_STATE_LOW,
    [GPIO_L293_LEFT_FRONT_A2]   = GPIO_STATE_LOW,
    [GPIO_L293_RIGHT_FRONT_A1]  = GPIO_STATE_LOW,
    [GPIO_L293_RIGHT_FRONT_A2]  = GPIO_STATE_LOW,
    [GPIO_L293_LEFT_REAR_A1]    = GPIO_STATE_LOW,
    [GPIO_L293_LEFT_REAR_A2]    = GPIO_STATE_LOW,
    [GPIO_L293_RIGHT_REAR_A1]   = GPIO_STATE_LOW,
    [GPIO_L293_RIGHT_REAR_A2]   = GPIO_STATE_LOW,
    [GPIO_DUALSHOCK2_ATTENTION] = GPIO_STATE_LOW,
};

static bool modes_applied = false;
static bool states_applied = false;

bool
gpio_verify_output_initialized(gpio_pin_t pin)
{
    return initialized_outputs[pin];
}

bool
gpio_verify_modes_applied(void)
{
    return modes_applied;
}

bool
gpio_verify_output_set(gpio_pin_t pin, gpio_state_t state)
{
    return pin_states[pin] == state;
}

bool
gpio_verify_states_applied(void)
{
    return states_applied;
}

void
gpio_init_output(gpio_pin_t pin)
{
    initialized_outputs[pin] = true;
    modes_applied = false;
}

void
gpio_apply_modes(void)
{
    modes_applied = true;
}

void
gpio_set_output(gpio_pin_t pin, gpio_state_t state)
{
    pin_states[pin] = state;
    states_applied = false;
}

void
gpio_apply_states(void)
{
    states_applied = true;
}

void
gpio_reset_modes(void)
{
    for (int i = 0; i < GPIO_SIZE; i++)
    {
        initialized_outputs[i] = false;
    }

    modes_applied = false;
}

void
gpio_reset_states(void)
{
    for (int i = 0; i < GPIO_SIZE; i++)
    {
        pin_states[i] = GPIO_STATE_LOW;
    }

    states_applied = false;
}