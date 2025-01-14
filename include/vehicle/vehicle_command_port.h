#ifndef _VEHICLE_COMMAND_H
#define _VEHICLE_COMMAND_H

#include "vehicle.h"

void
vehicle_command_init(void);

void
vehicle_command_receive(vehicle_t *self);

#endif