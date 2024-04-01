#include "l293.h"
#include <stdbool.h>

static void
update_gpio(void);

static bool gpio_reg_used[3] = {
    [HAL_GPIO_REGISTER_B] = false,
    [HAL_GPIO_REGISTER_C] = false,
    [HAL_GPIO_REGISTER_D] = false,
};

static uint8_t gpio_state[3] = {
    [HAL_GPIO_REGISTER_B] = 0,
    [HAL_GPIO_REGISTER_C] = 0,
    [HAL_GPIO_REGISTER_D] = 0,
};

void
l293_init(const l293_channel_t *channel)
{
    hal_gpio_register_t register1 = hal_gpio_get_register(channel->a1.pin);
    hal_gpio_register_t register2 = hal_gpio_get_register(channel->a2.pin);
    hal_gpio_init(&channel->a1);
    hal_gpio_init(&channel->a2);
    gpio_reg_used[register1] = true;
    gpio_reg_used[register2] = true;
}

void
l293_set_channel(const l293_function_t function, const l293_channel_t *channel)
{
    hal_gpio_register_t register1 = hal_gpio_get_register(channel->a1.pin);
    hal_gpio_register_t register2 = hal_gpio_get_register(channel->a2.pin);
    uint8_t index1 = hal_gpio_get_index(channel->a1.pin);
    uint8_t index2 = hal_gpio_get_index(channel->a2.pin);

    switch (function)
    {
        case L293_TURN_RIGHT:
            gpio_state[register1] &= ~(1 << index1);
            gpio_state[register2] |= (1 << index2);
            break;
        case L293_TURN_LEFT:
            gpio_state[register1] |= (1 << index1);
            gpio_state[register2] &= ~(1 << index2);
            break;
        case L293_STOP:
        default:
            gpio_state[register1] &= ~(1 << index1);
            gpio_state[register2] &= ~(1 << index2);
            break;
    }
}

void
l293_enable(const hal_timer0_pwm_t *pwm)
{
    update_gpio();
    hal_timer0_pwm_run(pwm);
}

void
l293_free_running_stop(const hal_timer0_pwm_t *pwm)
{
    update_gpio();
    hal_timer0_pwm_stop(pwm);
}

void
l293_fast_stop(void)
{
    update_gpio();
}

static void
update_gpio(void)
{
    for (uint8_t i = 1; i < 3; i++)
    {
        if (gpio_reg_used[i])
        {
            hal_gpio_write_mask(i, gpio_state[i]);
        }
    }
}
