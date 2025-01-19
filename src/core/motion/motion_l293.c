#include "gpio.h"
#include "motion.h"
#include "pwm.h"

static void
motion_gpio_set(motion_direction_t direction, gpio_pin_t a1, gpio_pin_t a2);

void
motion_init(void)
{
    gpio_init_output(GPIO_L293_LEFT_FRONT_A1);
    gpio_init_output(GPIO_L293_LEFT_FRONT_A2);
    gpio_init_output(GPIO_L293_RIGHT_FRONT_A1);
    gpio_init_output(GPIO_L293_RIGHT_FRONT_A2);
    gpio_init_output(GPIO_L293_LEFT_REAR_A1);
    gpio_init_output(GPIO_L293_LEFT_REAR_A2);
    gpio_init_output(GPIO_L293_RIGHT_REAR_A1);
    gpio_init_output(GPIO_L293_RIGHT_REAR_A2);

    pwm_init();
}

void
motion_apply(motion_t *self, bool is_soft_stop)
{
    pwm_stop();

    motion_gpio_set(
        self->left_front, GPIO_L293_LEFT_FRONT_A1, GPIO_L293_LEFT_FRONT_A2);

    motion_gpio_set(
        self->right_front, GPIO_L293_RIGHT_FRONT_A1, GPIO_L293_RIGHT_FRONT_A2);

    motion_gpio_set(
        self->left_rear, GPIO_L293_LEFT_REAR_A1, GPIO_L293_LEFT_REAR_A2);

    motion_gpio_set(
        self->right_rear, GPIO_L293_RIGHT_REAR_A1, GPIO_L293_RIGHT_REAR_A2);

    if (!is_soft_stop)
    {
        pwm_run();
    }
}

static void
motion_gpio_set(motion_direction_t direction, gpio_pin_t a1, gpio_pin_t a2)
{
    switch (direction)
    {
        case MOTION_FORWARD:
            gpio_set_output(a1, GPIO_STATE_LOW);
            gpio_set_output(a2, GPIO_STATE_HIGH);
            break;
        case MOTION_BACKWARD:
            gpio_set_output(a1, GPIO_STATE_HIGH);
            gpio_set_output(a2, GPIO_STATE_LOW);
            break;
        case MOTION_NONE:
        default:
            gpio_set_output(a1, GPIO_STATE_LOW);
            gpio_set_output(a2, GPIO_STATE_LOW);
    }
}