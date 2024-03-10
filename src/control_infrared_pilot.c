#include "control.h"
#include "infrared_pilot.h"

void
control_init(void)
{
    infrared_pilot_init();
}

control_command_t
control_read(void)
{
    infrared_pilot_command_t irp_cmd = infrared_pilot_read();
    switch (irp_cmd)
    {
        case IRP_CMD_2:
            return CTRL_MOVE_FACE_FORWARD;
        case IRP_CMD_8:
            return CTRL_MOVE_FACE_BACKWARD;
        case IRP_CMD_6:
            return CTRL_ROTATE_SIDE_LEFT_FORWARD;
        case IRP_CMD_4:
            return CTRL_ROTATE_SIDE_RIGHT_FORWARD;
        case IRP_CMD_FORWARD:
            return CTRL_MOVE_SIDE_RIGHT;
        case IRP_CMD_REWIND:
            return CTRL_MOVE_SIDE_LEFT;
        case IRP_CMD_3:
            return CTRL_MOVE_DIAG_FORWARD_RIGHT;
        case IRP_CMD_1:
            return CTRL_MOVE_DIAG_FORWARD_LEFT;
        case IRP_CMD_9:
            return CTRL_MOVE_DIAG_BACKWARD_RIGHT;
        case IRP_CMD_7:
            return CTRL_MOVE_DIAG_BACKWARD_LEFT;
        case IRP_CMD_PLUS:
            return CTRL_ROTATE_RIGHT;
        case IRP_CMD_MINUS:
            return CTRL_ROTATE_LEFT;
        case IRP_CMD_C:
            return CTRL_ROTATE_FACE_FRONT_RIGHT;
        case IRP_CMD_0:
            return CTRL_ROTATE_FACE_FRONT_LEFT;
        case IRP_CMD_BACK:
            return CTRL_ROTATE_SIDE_RIGHT_BACKWARD;
        default:
            return CTRL_SOFT_STOP;
    }
}
