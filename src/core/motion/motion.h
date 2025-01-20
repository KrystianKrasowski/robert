#ifndef _VEHICLE_MOTION_H
#define _VEHICLE_MOTION_H

#include "gpio.h"
#include <stdbool.h>

typedef enum
{
    MOTION_FORWARD,
    MOTION_BACKWARD,
    MOTION_NONE,
} motion_direction_t;

typedef struct motion_wheel
{
    gpio_t            a1;
    gpio_t            a2;
    motion_direction_t direction;
} motion_wheel_t;

typedef struct motion
{
    motion_wheel_t left_front;
    motion_wheel_t right_front;
    motion_wheel_t left_rear;
    motion_wheel_t right_rear;
} motion_t;

// void
// motion_init(motion_t *self);

void
motion_set_left_front(motion_t *self, motion_direction_t direction);

void
motion_set_right_front(motion_t *self, motion_direction_t direction);

void
motion_set_left_rear(motion_t *self, motion_direction_t direction);

void
motion_set_right_rear(motion_t *self, motion_direction_t direction);

void
motion_apply(motion_t *self, bool is_soft_stop);

#endif