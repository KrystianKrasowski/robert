#include "gpio.h"
#include "motion.h"
#include "pwm.h"
#include <string.h>

typedef struct motion_wheel
{
    gpio_t             a1;
    gpio_t             a2;
    motion_direction_t direction;
} l293_channel_t;

typedef struct motion
{
    l293_channel_t left_front;
    l293_channel_t right_front;
    l293_channel_t left_rear;
    l293_channel_t right_rear;
} motion_t;

static motion_t singleton;

static void
motion_set_wheel(l293_channel_t wheel);

void
motion_init(void)
{
    pwm_init();
    
    singleton.left_front.a1        = gpio_create(GPIO_L293_LEFT_FRONT_A1);
    singleton.left_front.a2        = gpio_create(GPIO_L293_LEFT_FRONT_A2);
    singleton.left_front.direction = MOTION_NONE;
    singleton.right_front.a1       = gpio_create(GPIO_L293_RIGHT_FRONT_A1);
    singleton.right_front.a2       = gpio_create(GPIO_L293_RIGHT_FRONT_A2);
    singleton.left_front.direction = MOTION_NONE;
    singleton.left_rear.a1         = gpio_create(GPIO_L293_LEFT_REAR_A1);
    singleton.left_rear.a2         = gpio_create(GPIO_L293_LEFT_REAR_A2);
    singleton.left_rear.direction  = MOTION_NONE;
    singleton.right_rear.a1        = gpio_create(GPIO_L293_RIGHT_REAR_A1);
    singleton.right_rear.a2        = gpio_create(GPIO_L293_RIGHT_REAR_A2);
    singleton.right_rear.direction = MOTION_NONE;
}

void
motion_set_left_front(motion_direction_t direction)
{
    singleton.left_front.direction = direction;
}

void
motion_set_right_front(motion_direction_t direction)
{
    singleton.right_front.direction = direction;
}

void
motion_set_left_rear(motion_direction_t direction)
{
    singleton.left_rear.direction = direction;
}

void
motion_set_right_rear(motion_direction_t direction)
{
    singleton.right_rear.direction = direction;
}

void
motion_apply(bool is_soft_stop)
{
    pwm_stop();

    motion_set_wheel(singleton.left_front);
    motion_set_wheel(singleton.right_front);
    motion_set_wheel(singleton.left_rear);
    motion_set_wheel(singleton.right_rear);

    if (!is_soft_stop)
    {
        pwm_run();
    }
}

static void
motion_set_wheel(l293_channel_t wheel)
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