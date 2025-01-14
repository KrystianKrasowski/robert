#ifndef _VEHICLE_MOTION_MOCK_H
#define _VEHICLE_MOTION_MOCK_H

#include "vehicle.h"
#include <stdbool.h>

bool
vehicle_motion_mock_is_initialized(void);

bool
vehicle_motion_mock_verify_command(vehicle_command_t command);

#endif