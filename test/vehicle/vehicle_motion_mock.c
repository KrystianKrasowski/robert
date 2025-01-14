#include "vehicle_motion_mock.h"
#include "vehicle_motion_port.h"

static bool initialized = false;
static vehicle_command_t applied_command = -1;

void
vehicle_motion_init(void)
{
    initialized = true;
}

void
vehicle_motion_apply(vehicle_t *self)
{
    applied_command = self->current_command;
}

bool
vehicle_motion_mock_is_initialized(void)
{
    return initialized;
}

bool
vehicle_motion_mock_verify_command(vehicle_command_t command)
{
    return command == applied_command;
}