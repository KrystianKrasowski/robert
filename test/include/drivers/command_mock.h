#ifndef _VEHICLE_COMMAND_MOCK_H
#define _VEHICLE_COMMAND_MOCK_H

#include "vehicle.h"
#include "drivers/command.h"
#include <stdbool.h>

bool
command_mock_is_initilized(void);

void
command_mock_given_command(command_t command);

#endif