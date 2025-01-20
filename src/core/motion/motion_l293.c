#include "gpio.h"
#include "motion.h"
#include "pwm.h"

static void
motion_set_wheel(motion_wheel_t wheel);

static gpio_t left_front_a1  = {GPIO_L293_LEFT_FRONT_A1};
static gpio_t left_front_a2  = {GPIO_L293_LEFT_FRONT_A2};
static gpio_t right_front_a1 = {GPIO_L293_RIGHT_FRONT_A1};
static gpio_t right_front_a2 = {GPIO_L293_RIGHT_FRONT_A2};
static gpio_t left_rear_a1   = {GPIO_L293_LEFT_REAR_A1};
static gpio_t left_rear_a2   = {GPIO_L293_LEFT_REAR_A2};
static gpio_t right_rear_a1  = {GPIO_L293_RIGHT_REAR_A1};
static gpio_t right_rear_a2  = {GPIO_L293_RIGHT_REAR_A2};

void
motion_init(void)
{
    gpio_init(&left_front_a1);
    gpio_init(&left_front_a2);
    gpio_init(&right_front_a1);
    gpio_init(&right_front_a2);
    gpio_init(&left_rear_a1);
    gpio_init(&left_rear_a2);
    gpio_init(&right_rear_a1);
    gpio_init(&right_rear_a2);
    pwm_init();
}

void
motion_set_left_front(motion_t *self, motion_direction_t direction)
{
    self->left_front.direction = direction;
}

void
motion_set_right_front(motion_t *self, motion_direction_t direction)
{
    self->right_front.direction = direction;
}

void
motion_set_left_rear(motion_t *self, motion_direction_t direction)
{
    self->left_rear.direction = direction;
}

void
motion_set_right_rear(motion_t *self, motion_direction_t direction)
{
    self->right_rear.direction = direction;
}

void
motion_apply(motion_t *self, bool is_soft_stop)
{
    pwm_stop();

    motion_set_wheel(self->left_front);
    motion_set_wheel(self->right_front);
    motion_set_wheel(self->left_rear);
    motion_set_wheel(self->right_rear);

    if (!is_soft_stop)
    {
        pwm_run();
    }
}

static void
motion_set_wheel(motion_wheel_t wheel)
{
    switch (wheel.direction)
    {
        case MOTION_FORWARD:
            gpio_set_state(&wheel.a1, GPIO_STATE_LOW);
            gpio_set_state(&wheel.a2, GPIO_STATE_HIGH);
            break;
        case MOTION_BACKWARD:
            gpio_set_state(&wheel.a1, GPIO_STATE_HIGH);
            gpio_set_state(&wheel.a2, GPIO_STATE_LOW);
            break;
        case MOTION_NONE:
        default:
            gpio_set_state(&wheel.a1, GPIO_STATE_LOW);
            gpio_set_state(&wheel.a2, GPIO_STATE_LOW);
    }
}