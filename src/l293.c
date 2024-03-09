#include "l293.h"
#include <stdbool.h>

static void
update_gpio(void);

static bool gpio_reg_used[3] = {
    [HAL_GPIO_REGB] = false,
    [HAL_GPIO_REGC] = false,
    [HAL_GPIO_REGD] = false,
};

static uint8_t gpio_state[3] = {
    [HAL_GPIO_REGB] = 0,
    [HAL_GPIO_REGC] = 0,
    [HAL_GPIO_REGD] = 0,
};

void
l293_init(const l293_channel_t *channel)
{
    hal_gpio_init(&channel->a1);
    hal_gpio_init(&channel->a2);
    gpio_reg_used[channel->a1.reg] = true;
    gpio_reg_used[channel->a2.reg] = true;
}

void
l293_set_channel(const l293_function_t function, const l293_channel_t *channel)
{
    switch (function)
    {
        case L293_TURN_RIGHT:
            gpio_state[channel->a1.reg] &= ~(1 << channel->a1.pin);
            gpio_state[channel->a2.reg] |= (1 << channel->a2.pin);
            break;
        case L293_TURN_LEFT:
            gpio_state[channel->a1.reg] |= (1 << channel->a1.pin);
            gpio_state[channel->a2.reg] &= ~(1 << channel->a2.pin);
            break;
        case L293_FAST_STOP:
        default:
            gpio_state[channel->a1.reg] &= ~(1 << channel->a1.pin);
            gpio_state[channel->a2.reg] &= ~(1 << channel->a2.pin);
            break;
    }
}

void
l293_enable(const hal_t0pwm_def_t *pwm)
{
    update_gpio();
    hal_t0pwm_run(pwm);
}

void
l293_disable(void)
{
    update_gpio();
    hal_t0pwm_stop();
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
