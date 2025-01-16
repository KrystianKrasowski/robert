#include "drivers/command.h"

void
command_init(void)
{}

command_t
command_receive(void)
{
    return COMMAND_MOVE_FACE_FORWARD;
}