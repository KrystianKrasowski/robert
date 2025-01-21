#include "gpio.h"
#include "pwm.h"

// led is PB3
#define LED_PIN GPIO_ODR_3

int
main(void)
{
    gpio_t left_front_a1  = gpio_create(GPIO_L293_LEFT_FRONT_A1);
    gpio_t left_front_a2  = gpio_create(GPIO_L293_LEFT_FRONT_A2);
    gpio_t right_front_a1 = gpio_create(GPIO_L293_RIGHT_FRONT_A1);
    gpio_t right_front_a2 = gpio_create(GPIO_L293_RIGHT_FRONT_A2);
    gpio_t left_rear_a1   = gpio_create(GPIO_L293_LEFT_REAR_A1);
    gpio_t left_rear_a2   = gpio_create(GPIO_L293_LEFT_REAR_A2);
    gpio_t right_rear_a1  = gpio_create(GPIO_L293_RIGHT_REAR_A1);
    gpio_t right_rear_a2  = gpio_create(GPIO_L293_RIGHT_REAR_A2);
    gpio_set_state(&left_front_a1, GPIO_STATE_HIGH);
    gpio_set_state(&left_front_a2, GPIO_STATE_HIGH);
    gpio_set_state(&right_front_a1, GPIO_STATE_HIGH);
    gpio_set_state(&right_front_a2, GPIO_STATE_HIGH);
    gpio_set_state(&left_rear_a1, GPIO_STATE_HIGH);
    gpio_set_state(&left_rear_a2, GPIO_STATE_HIGH);
    gpio_set_state(&right_rear_a1, GPIO_STATE_HIGH);
    gpio_set_state(&right_rear_a2, GPIO_STATE_HIGH);

    pwm_init();
    pwm_run();

    while (1)
    {
    }

    return 0;
}