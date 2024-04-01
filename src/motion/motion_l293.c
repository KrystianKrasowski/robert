#include "l293.h"
#include "motion.h"
#include <avrhal/gpio.h>
#include <avrhal/timer0_pwm.h>

static hal_gpio_t pwm_gpio = {
    .direction = HAL_GPIO_OUTPUT,
    .pin       = HAL_GPIO_PD6,
};

static hal_timer0_pwm_t pwm = {
    .mode = HAL_TIMER0_PWM_PHASE_CORRECT,
    .channel_a =
        {
            .mode       = HAL_TIMER0_PWM_CHANNEL_NON_INVERTING,
            .duty_cycle = 75,
        },
    .channel_b =
        {
            .mode       = HAL_TIMER0_PWM_CHANNEL_DISCONNECTED,
            .duty_cycle = 0,
        },
    .prescaller = HAL_TIMER_PRESCALLER_256,
};

static l293_channel_t motors[4] = {
    [MOTION_MOTOR_LEFT_FRONT] =
        {
            .a1 = {HAL_GPIO_PC3, HAL_GPIO_OUTPUT},
            .a2 = {HAL_GPIO_PC2, HAL_GPIO_OUTPUT},
        },

    [MOTION_MOTOR_LEFT_REAR] =
        {
            .a1 = {HAL_GPIO_PC5, HAL_GPIO_OUTPUT},
            .a2 = {HAL_GPIO_PC4, HAL_GPIO_OUTPUT},
        },

    [MOTION_MOTOR_RIGHT_FRONT] =
        {
            .a1 = {HAL_GPIO_PD0, HAL_GPIO_OUTPUT},
            .a2 = {HAL_GPIO_PD1, HAL_GPIO_OUTPUT},
        },

    [MOTION_MOTOR_RIGHT_REAR] =
        {
            .a1 = {HAL_GPIO_PD2, HAL_GPIO_OUTPUT},
            .a2 = {HAL_GPIO_PD3, HAL_GPIO_OUTPUT},
        },
};

void
motion_init(void)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        l293_init(&motors[i]);
    }

    hal_gpio_init(&pwm_gpio);
    hal_timer0_pwm_init(&pwm);
}

void
motion_set(const motion_t *motion)
{
    l293_function_t function;
    switch (motion->direction)
    {
        case MOTION_DIR_FWD:
            function = L293_TURN_RIGHT;
            break;
        case MOTION_DIR_BCK:
            function = L293_TURN_LEFT;
            break;
        case MOTION_DIR_STOP:
        default:
            function = L293_STOP;
    }

    l293_set_channel(function, &motors[motion->motor]);
}

void
motion_run(void)
{
    l293_enable(&pwm);
}

void
motion_stop_running(void)
{
    l293_free_running_stop(&pwm);
}

void
motion_stop(void)
{
    l293_fast_stop();
}
