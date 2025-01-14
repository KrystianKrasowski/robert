#ifndef _VEHICLE_MOTION_H
#define _VEHICLE_MOTION_H

#include "vehicle.h"

void
vehicle_motion_init(void);

void
vehicle_motion_apply(vehicle_t *self);

#endif