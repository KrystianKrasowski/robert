#ifndef _L293_H
#define _L293_H

#include <avrhal/gpio.h>
#include <avrhal/std.h>
#include <avrhal/timer0.h>
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
l293_init(const l293_channel_t *channel);

void
l293_set_channel(const l293_function_t function, const l293_channel_t *channel);

void
l293_enable(const hal_timer_prescaller_t prescaller);

void
l293_free_running_stop(void);

void
l293_fast_stop(void);

#endif
