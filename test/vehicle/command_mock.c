#include "drivers/command.h"
#include <stdbool.h>

static bool initialized = false;
static command_t given_command = -1;

void
command_init(void)
{
    initialized = true;
}

command_t
command_receive()
{
    return given_command;
}

bool
command_mock_is_initilized(void)
{
    return initialized;
}

void
command_mock_given_command(command_t command)
{
    given_command = command;
}