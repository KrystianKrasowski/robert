#include "l293.h"
#include "motion.h"
#include <avrhal/gpio.h>
#include <avrhal/t0pwm.h>

static hal_gpio_def_t pwm_gpio = {
    .reg = HAL_GPIO_REGD,
    .dir = HAL_GPIO_OUTPUT,
    .pin = 6,
};

static hal_t0pwm_def_t pwm = {
    .mode = HAL_T0PWM_MODE_PHASE_CORRECT,
    .channel_a = {HAL_T0PWM_CHANNEL_NON_INVERTING, 75},
    .channel_b = {HAL_T0PWM_CHANNEL_DISCONNECTED, 0},
    .prescaller = HAL_TIMER_PRESCALLER_256,
};

static l293_channel_t motors[4] = {
    [MOTION_MOTOR_LEFT_FRONT] =
        {
            .a1 = {HAL_GPIO_REGC, HAL_GPIO_OUTPUT, 3},
            .a2 = {HAL_GPIO_REGC, HAL_GPIO_OUTPUT, 2},
        },

    [MOTION_MOTOR_LEFT_REAR] =
        {
            .a1 = {HAL_GPIO_REGC, HAL_GPIO_OUTPUT, 5},
            .a2 = {HAL_GPIO_REGC, HAL_GPIO_OUTPUT, 4},
        },

    [MOTION_MOTOR_RIGHT_FRONT] =
        {
            .a1 = {HAL_GPIO_REGD, HAL_GPIO_OUTPUT, 0},
            .a2 = {HAL_GPIO_REGD, HAL_GPIO_OUTPUT, 1},
        },

    [MOTION_MOTOR_RIGHT_REAR] =
        {
            .a1 = {HAL_GPIO_REGD, HAL_GPIO_OUTPUT, 2},
            .a2 = {HAL_GPIO_REGD, HAL_GPIO_OUTPUT, 3},
        },
};

void motion_init(void)
{
  for (uint8_t i = 0; i < 4; i++)
  {
    l293_init(&motors[i]);
  }

  hal_gpio_init(&pwm_gpio);
  hal_t0pwm_init(&pwm);
}

void motion_set(const motion_t *motion)
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
      function = L293_FAST_STOP;
  }

  l293_set_channel(function, &motors[motion->motor]);
}

void motion_run(void) { l293_enable(&pwm); }

void motion_stop(void) { l293_disable(); }
