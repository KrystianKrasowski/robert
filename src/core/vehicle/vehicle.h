#ifndef _VEHICLE_H
#define _VEHICLE_H

#include "motion.h"

typedef struct vehicle
{
    motion_t motion;
} vehicle_t;

// void
// vehicle_init(vehicle_t *self);

void
vehicle_run(vehicle_t *self);

#endif