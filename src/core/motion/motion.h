#ifndef _VEHICLE_MOTION_H
#define _VEHICLE_MOTION_H

#include <stdbool.h>

typedef enum
{
    MOTION_FORWARD,
    MOTION_BACKWARD,
    MOTION_NONE,
} motion_direction_t;

void
motion_init();

void
motion_set_left_front(motion_direction_t direction);

void
motion_set_right_front(motion_direction_t direction);

void
motion_set_left_rear(motion_direction_t direction);

void
motion_set_right_rear(motion_direction_t direction);

void
motion_apply(bool is_soft_stop);

#endif