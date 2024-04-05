#include "l293.h"
#include <stdbool.h>

void
l293_init(const l293_channel_t *channel)
{
    hal_gpio_define(&channel->a1);
    hal_gpio_define(&channel->a2);
    hal_gpio_update();
}

void
l293_set_channel(const l293_function_t function, const l293_channel_t *channel)
{
    switch (function)
    {
        case L293_TURN_RIGHT:
            hal_gpio_set(&channel->a1, HAL_GPIO_LOW);
            hal_gpio_set(&channel->a2, HAL_GPIO_HIGH);
            break;
        case L293_TURN_LEFT:
            hal_gpio_set(&channel->a1, HAL_GPIO_HIGH);
            hal_gpio_set(&channel->a2, HAL_GPIO_LOW);
            break;
        case L293_STOP:
        default:
            hal_gpio_set(&channel->a1, HAL_GPIO_LOW);
            hal_gpio_set(&channel->a2, HAL_GPIO_LOW);
            break;
    }
}

void
l293_enable(const hal_timer0_pwm_t *pwm)
{
    hal_gpio_update();
    hal_timer0_pwm_run(pwm);
}

void
l293_free_running_stop(const hal_timer0_pwm_t *pwm)
{
    hal_gpio_update();
    hal_timer0_pwm_stop(pwm);
}

void
l293_fast_stop(void)
{
    hal_gpio_update();
}
