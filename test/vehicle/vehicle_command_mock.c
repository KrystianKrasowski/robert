#include "vehicle_command_port.h"
#include "vehicle_command_mock.h"

static bool initialized = false;
static vehicle_command_t given_command = -1;

void
vehicle_command_init(void)
{
    initialized = true;
}

void
vehicle_command_receive(vehicle_t *self)
{
    self->current_command = given_command;
}

bool
vehicle_command_mock_is_initilized(void)
{
    return initialized;
}

void
vehicle_command_mock_given_command(vehicle_command_t command)
{
    given_command = command;
}