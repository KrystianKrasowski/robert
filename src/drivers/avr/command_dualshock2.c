#include "drivers/command.h"
#include "drivers/dualshock2.h"

void
command_init(void)
{
    dualshock2_init();
}

command_t
command_receive(void)
{
    uint16_t ds2 = dualshock2_read();

    switch (ds2)
    {
        case DS2_UP:
            return COMMAND_MOVE_FACE_FORWARD;
        case DS2_DOWN:
            return COMMAND_MOVE_FACE_BACKWARD;
        case DS2_RIGHT:
            return COMMAND_MOVE_SIDE_RIGHT;
        case DS2_LEFT:
            return COMMAND_MOVE_SIDE_LEFT;
        case DS2_UP | DS2_RIGHT:
            return COMMAND_MOVE_DIAG_FORWARD_RIGHT;
        case DS2_UP | DS2_LEFT:
            return COMMAND_MOVE_DIAG_FORWARD_LEFT;
        case DS2_DOWN | DS2_RIGHT:
            return COMMAND_MOVE_DIAG_BACKWARD_RIGHT;
        case DS2_DOWN | DS2_LEFT:
            return COMMAND_MOVE_DIAG_BACKWARD_LEFT;
        case DS2_UP | DS2_SQUARE:
            return COMMAND_ROTATE_SIDE_RIGHT_FORWARD;
        case DS2_UP | DS2_CIRCLE:
            return COMMAND_ROTATE_SIDE_LEFT_FORWARD;
        case DS2_DOWN | DS2_SQUARE:
            return COMMAND_ROTATE_SIDE_RIGHT_BACKWARD;
        case DS2_DOWN | DS2_CIRCLE:
            return COMMAND_ROTATE_SIDE_LEFT_BACKWARD;
        case DS2_UP | DS2_CROSS:
            return COMMAND_ROTATE_RIGHT;
        case DS2_DOWN | DS2_TRIANGLE:
            return COMMAND_ROTATE_LEFT;
        case DS2_R1:
            return COMMAND_ROTATE_FACE_FRONT_RIGHT;
        case DS2_L1:
            return COMMAND_ROTATE_FACE_FRONT_LEFT;
        case DS2_R2:
            return COMMAND_ROTATE_FACE_REAR_RIGHT;
        case DS2_L2:
            return COMMAND_ROTATE_FACE_REAR_LEFT;
        default:
            return COMMAND_SOFT_STOP;
    }
}