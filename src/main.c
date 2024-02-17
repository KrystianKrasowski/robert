#include "comm.h"
#include <avrhal/gpio.h>
#include <avrhal/t0pwm.h>

hal_t0pwm_def_t pwm = {
    .mode = HAL_T0PWM_MODE_PHASE_CORRECT,
    .channel_a = {.mode = HAL_T0PWM_CHANNEL_NON_INVERTING, .duty_cycle = 50},
    .channel_b = {.mode = HAL_T0PWM_CHANNEL_DISCONNECTED, .duty_cycle = 0},
    .prescaller = HAL_T0PWM_PRESC_8};

typedef struct
{
  hal_gpio_def_t a1;
  hal_gpio_def_t a2;
} l293_def_t;

void l293_init(const l293_def_t *def)
{
  hal_gpio_init(&def->a1);
  hal_gpio_init(&def->a2);
}

void l293_right(const l293_def_t *def)
{
  hal_gpio_write(&def->a1, HAL_GPIO_LOW);
  hal_gpio_write(&def->a2, HAL_GPIO_HIGH);
}

void l293_left(const l293_def_t *def)
{
  hal_gpio_write(&def->a1, HAL_GPIO_HIGH);
  hal_gpio_write(&def->a2, HAL_GPIO_LOW);
}

void l293_stop(const l293_def_t *def)
{
  hal_gpio_write(&def->a1, HAL_GPIO_LOW);
  hal_gpio_write(&def->a2, HAL_GPIO_LOW);
}

l293_def_t wheel_left_front =
    {.a1 = {.reg = HAL_GPIO_REGC, .dir = HAL_GPIO_OUTPUT, .pin = 3},
     .a2 = {.reg = HAL_GPIO_REGC, .dir = HAL_GPIO_OUTPUT, .pin = 2}};

l293_def_t wheel_left_back =
    {.a1 = {.reg = HAL_GPIO_REGC, .dir = HAL_GPIO_OUTPUT, .pin = 5},
     .a2 = {.reg = HAL_GPIO_REGC, .dir = HAL_GPIO_OUTPUT, .pin = 4}};

l293_def_t wheel_right_front =
    {.a1 = {.reg = HAL_GPIO_REGD, .dir = HAL_GPIO_OUTPUT, .pin = 0},
     .a2 = {.reg = HAL_GPIO_REGD, .dir = HAL_GPIO_OUTPUT, .pin = 1}};

l293_def_t wheel_right_back =
    {.a1 = {.reg = HAL_GPIO_REGD, .dir = HAL_GPIO_OUTPUT, .pin = 2},
     .a2 = {.reg = HAL_GPIO_REGD, .dir = HAL_GPIO_OUTPUT, .pin = 3}};

void apply(comm_command_t command);
void mov_move_forward(void);
void mov_move_backward(void);
void mov_turn_right(void);
void mov_turn_left(void);
void mov_move_right(void);
void mov_move_left(void);
void mov_move_left_back_forward(void);
void mov_move_left_front_forward(void);
void mov_move_right_back_backward(void);
void mov_move_right_front_backward(void);
void mov_stay();

int main(void)
{
  l293_init(&wheel_left_front);
  l293_init(&wheel_left_back);
  l293_init(&wheel_right_front);
  l293_init(&wheel_right_back);
  hal_t0pwm_init(&pwm);
  comm_init();

  while (1)
  {
    comm_command_t command = comm_read();
    apply(command);
  }

  return 0;
}

void apply(comm_command_t command)
{
  switch (command)
  {
    case COMM_MOVE_FORWARD:
      mov_move_forward();
      break;
    case COMM_MOVE_BACKWARD:
      mov_move_backward();
      break;
    case COMM_MOVE_RIGHT:
      mov_move_right();
      break;
    case COMM_MOVE_LEFT:
      mov_move_left();
      break;
    case COMM_TURN_RIGHT:
      mov_turn_right();
      break;
    case COMM_TURN_LEFT:
      mov_turn_left();
      break;
    case COMM_LEFT_BACK_FORWARD:
      mov_move_left_back_forward();
      break;
    case COMM_LEFT_FRONT_FORWARD:
      mov_move_left_front_forward();
      break;
    case COMM_RIGHT_BACK_BACKWARD:
      mov_move_right_back_backward();
      break;
    case COMM_RIGHT_FRONT_BACKWARD:
      mov_move_right_front_backward();
      break;
    case COMM_STAY:
      mov_stay();
      break;
  }
}

void mov_move_forward(void)
{
  l293_right(&wheel_left_front);
  l293_right(&wheel_left_back);
  l293_right(&wheel_right_front);
  l293_right(&wheel_right_back);
  hal_t0pwm_run(&pwm);
}

void mov_move_backward(void)
{
  l293_left(&wheel_left_front);
  l293_left(&wheel_left_back);
  l293_left(&wheel_right_front);
  l293_left(&wheel_right_back);
  hal_t0pwm_run(&pwm);
}

void mov_move_right(void)
{
  l293_right(&wheel_left_front);
  l293_left(&wheel_left_back);
  l293_left(&wheel_right_front);
  l293_right(&wheel_right_back);
  hal_t0pwm_run(&pwm);
}

void mov_move_left(void)
{
  l293_left(&wheel_left_front);
  l293_right(&wheel_left_back);
  l293_right(&wheel_right_front);
  l293_left(&wheel_right_back);
  hal_t0pwm_run(&pwm);
}

void mov_turn_right(void)
{
  l293_right(&wheel_left_front);
  l293_right(&wheel_left_back);
  hal_t0pwm_run(&pwm);
}

void mov_turn_left(void)
{
  l293_right(&wheel_right_front);
  l293_right(&wheel_right_back);
  hal_t0pwm_run(&pwm);
}

void mov_move_left_back_forward(void)
{
  l293_right(&wheel_left_back);
  hal_t0pwm_run(&pwm);
}

void mov_move_left_front_forward(void)
{
  l293_right(&wheel_left_front);
  hal_t0pwm_run(&pwm);
}

void mov_move_right_back_backward(void)
{
  l293_left(&wheel_right_back);
  hal_t0pwm_run(&pwm);
}

void mov_move_right_front_backward(void)
{
  l293_left(&wheel_right_front);
  hal_t0pwm_run(&pwm);
}

void mov_stay(void)
{
  l293_stop(&wheel_left_front);
  l293_stop(&wheel_left_back);
  l293_stop(&wheel_right_front);
  l293_stop(&wheel_right_back);
  hal_t0pwm_stop();
}