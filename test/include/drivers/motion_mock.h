#ifndef _VEHICLE_MOTION_MOCK_H
#define _VEHICLE_MOTION_MOCK_H

#include "vehicle.h"
#include "drivers/command.h"
#include <stdbool.h>

bool
motion_mock_is_initialized(void);

bool
motion_mock_verify_left_front(motion_direction_t direction);

bool
motion_mock_verify_right_front(motion_direction_t direction);

bool
motion_mock_verify_left_rear(motion_direction_t direction);

bool
motion_mock_verify_right_rear(motion_direction_t direction);

#endif