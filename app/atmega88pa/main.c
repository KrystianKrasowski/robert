#include "command.h"
#include "pwm.h"
#include "vehicle.h"
#include <avr/interrupt.h>

static vehicle_t
vehicle_create(void);

static motion_wheel_t
create_wheel(gpio_pin_t a1_pin, gpio_pin_t a2_pin);

int
main(void)
{
    sei();
    command_init();
    pwm_init();
    vehicle_t vehicle = vehicle_create();

    while (1)
    {
        vehicle_run(&vehicle);
    }

    return 0;
}

static vehicle_t
vehicle_create(void)
{
    motion_wheel_t left_front =
        create_wheel(GPIO_L293_LEFT_FRONT_A1, GPIO_L293_LEFT_FRONT_A2);
    motion_wheel_t right_front =
        create_wheel(GPIO_L293_RIGHT_FRONT_A1, GPIO_L293_RIGHT_FRONT_A2);
    motion_wheel_t left_rear =
        create_wheel(GPIO_L293_LEFT_REAR_A1, GPIO_L293_LEFT_REAR_A2);
    motion_wheel_t right_rear =
        create_wheel(GPIO_L293_RIGHT_REAR_A1, GPIO_L293_RIGHT_REAR_A2);

    motion_t  motion  = {left_front, right_front, left_rear, right_rear};
    vehicle_t vehicle = {motion};

    return vehicle;
}

static motion_wheel_t
create_wheel(gpio_pin_t a1_pin, gpio_pin_t a2_pin)
{
    gpio_t a1 = {a1_pin};
    gpio_t a2 = {a2_pin};
    gpio_init(&a1);
    gpio_init(&a2);
    motion_wheel_t wheel = {a1, a2};

    return wheel;
}