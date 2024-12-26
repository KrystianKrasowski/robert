#ifndef _L293_H
#define _L293_H

#include <avrhal/gpio.h>
#include <avrhal/std.h>
#include <avrhal/timer0_pwm.h>
#include <stdint.h>

typedef struct
{
    hal_gpio_t a1;
    hal_gpio_t a2;
} l293_channel_t;

typedef enum
{
    L293_TURN_LEFT,
    L293_TURN_RIGHT,
    L293_STOP,
} l293_function_t;

void
l293_init(l293_channel_t const *channel);

void
l293_set_channel(l293_function_t const function, l293_channel_t const *channel);

void
l293_enable(hal_timer0_pwm_t const *pwm);

void
l293_free_running_stop(hal_timer0_pwm_t const *pwm);

void
l293_fast_stop(void);

#endif
