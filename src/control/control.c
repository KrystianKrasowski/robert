#include "control.h"
#include "dualshock2.h"

void
control_init(void)
{
    dualshock2_init();
}

control_command_t
control_read(void)
{
    uint16_t          ds2_state = dualshock2_read();

    switch (ds2_state)
    {
        case DS2_UP:
            return CTRL_MOVE_FACE_FORWARD;
        case DS2_DOWN:
            return CTRL_MOVE_FACE_BACKWARD;
        case DS2_RIGHT:
            return CTRL_MOVE_SIDE_RIGHT;
        case DS2_LEFT:
            return CTRL_MOVE_SIDE_LEFT;
        case DS2_UP | DS2_RIGHT:
            return CTRL_MOVE_DIAG_FORWARD_RIGHT;
        case DS2_UP | DS2_LEFT:
            return CTRL_MOVE_DIAG_FORWARD_LEFT;
        case DS2_DOWN | DS2_RIGHT:
            return CTRL_MOVE_DIAG_BACKWARD_RIGHT;
        case DS2_DOWN | DS2_LEFT:
            return CTRL_MOVE_DIAG_BACKWARD_LEFT;
        case DS2_UP | DS2_SQUARE:
            return CTRL_ROTATE_SIDE_RIGHT_FORWARD;
        case DS2_UP | DS2_CIRCLE:
            return CTRL_ROTATE_SIDE_LEFT_FORWARD;
        case DS2_DOWN | DS2_SQUARE:
            return CTRL_ROTATE_SIDE_RIGHT_BACKWARD;
        case DS2_DOWN | DS2_CIRCLE:
            return CTRL_ROTATE_SIDE_LEFT_BACKWARD;
        case DS2_UP | DS2_CROSS:
            return CTRL_ROTATE_RIGHT;
        case DS2_DOWN | DS2_TRIANGLE:
            return CTRL_ROTATE_LEFT;
        case DS2_R1:
            return CTRL_ROTATE_FACE_FRONT_RIGHT;
        case DS2_L1:
            return CTRL_ROTATE_FACE_FRONT_LEFT;
        case DS2_R2:
            return CTRL_ROTATE_FACE_REAR_RIGHT;
        case DS2_L2:
            return CTRL_ROTATE_FACE_REAR_LEFT;
        case DS2_L1 | DS2_L2 | DS2_R1 | DS2_R2:
            return CTRL_HARD_STOP;
        case DS2_NONE:
        default:
            return CTRL_SOFT_STOP;
    }
}
