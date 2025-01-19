#ifndef _VEHICLE_MOTION_H
#define _VEHICLE_MOTION_H

#include <stdbool.h>

typedef enum
{
    MOTION_FORWARD,
    MOTION_BACKWARD,
    MOTION_NONE,
} motion_direction_t;

typedef struct motion
{
    motion_direction_t left_front;
    motion_direction_t right_front;
    motion_direction_t left_rear;
    motion_direction_t right_rear;
} motion_t;


void
motion_init(void);

void
motion_apply(motion_t *self, bool is_soft_stop);

#endif