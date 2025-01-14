#ifndef _VEHICLE_COMMAND_MOCK_H
#define _VEHICLE_COMMAND_MOCK_H

#include "vehicle.h"
#include <stdbool.h>

bool
vehicle_command_mock_is_initilized(void);

void
vehicle_command_mock_given_command(vehicle_command_t command);

#endif