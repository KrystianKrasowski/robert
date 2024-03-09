#ifndef M_COMM
#endif
#define M_COMM 2

#include "comm.h"

#if M_COMM == 2
#include "ds2.h"

#define ROTATE_FACE_FRONT_RIGHT DS2_BUTTON_R1
#define ROTATE_FACE_FRONT_LEFT  DS2_BUTTON_L1
#define ROTATE_FACE_REAR_RIGHT  DS2_BUTTON_R2
#define ROTATE_FACE_REAR_LEFT   DS2_BUTTON_L2
#define STOP                    DS2_NONE

static uint16_t command_map[19] = {
    [COMM_MOVE_FACE_FORWARD]          = DS2_BUTTON_UP,
    [COMM_MOVE_FACE_BACKWARD]         = DS2_BUTTON_DOWN,
    [COMM_MOVE_SIDE_RIGHT]            = DS2_BUTTON_RIGHT,
    [COMM_MOVE_SIDE_LEFT]             = DS2_BUTTON_LEFT,
    [COMM_MOVE_DIAG_FORWARD_RIGHT]    = DS2_BUTTON_UP | DS2_BUTTON_RIGHT,
    [COMM_MOVE_DIAG_FORWARD_LEFT]     = DS2_BUTTON_UP | DS2_BUTTON_LEFT,
    [COMM_MOVE_DIAG_BACKWARD_RIGHT]   = DS2_BUTTON_DOWN | DS2_BUTTON_RIGHT,
    [COMM_MOVE_DIAG_BACKWARD_LEFT]    = DS2_BUTTON_DOWN | DS2_BUTTON_LEFT,
    [COMM_ROTATE_SIDE_RIGHT_FORWARD]  = DS2_BUTTON_UP | DS2_BUTTON_SQUARE,
    [COMM_ROTATE_SIDE_LEFT_FORWARD]   = DS2_BUTTON_UP | DS2_BUTTON_CIRCLE,
    [COMM_ROTATE_SIDE_RIGHT_BACKWARD] = DS2_BUTTON_DOWN | DS2_BUTTON_SQUARE,
    [COMM_ROTATE_SIDE_LEFT_BACKWARD]  = DS2_BUTTON_DOWN | DS2_BUTTON_CIRCLE,
    [COMM_ROTATE_RIGHT]               = DS2_BUTTON_UP | DS2_BUTTON_CROSS,
    [COMM_ROTATE_LEFT]                = DS2_BUTTON_DOWN | DS2_BUTTON_TRIANGLE,
    [COMM_ROTATE_FACE_FRONT_RIGHT]    = DS2_BUTTON_R1,
    [COMM_ROTATE_FACE_FRONT_LEFT]     = DS2_BUTTON_L1,
    [COMM_ROTATE_FACE_REAR_RIGHT]     = DS2_BUTTON_R2,
    [COMM_ROTATE_FACE_REAR_LEFT]      = DS2_BUTTON_L2,
};

static comm_command_t explicit_commands[6] = {
    COMM_ROTATE_SIDE_RIGHT_FORWARD,
    COMM_ROTATE_SIDE_LEFT_FORWARD,
    COMM_ROTATE_SIDE_RIGHT_BACKWARD,
    COMM_ROTATE_SIDE_LEFT_BACKWARD,
    COMM_ROTATE_RIGHT,
    COMM_ROTATE_LEFT,
};

static comm_command_t main_motion_commands[8] = {
    COMM_MOVE_FACE_FORWARD,
    COMM_MOVE_FACE_BACKWARD,
    COMM_MOVE_SIDE_RIGHT,
    COMM_MOVE_SIDE_LEFT,
    COMM_MOVE_DIAG_FORWARD_RIGHT,
    COMM_MOVE_DIAG_FORWARD_LEFT,
    COMM_MOVE_DIAG_BACKWARD_RIGHT,
    COMM_MOVE_DIAG_BACKWARD_LEFT,
};

static comm_command_t top_commands[4] = {
    COMM_ROTATE_FACE_FRONT_RIGHT,
    COMM_ROTATE_FACE_FRONT_LEFT,
    COMM_ROTATE_FACE_REAR_RIGHT,
    COMM_ROTATE_FACE_REAR_LEFT,
};

void
comm_init(void)
{
    ds2_init();
}

comm_command_t
comm_read(void)
{
    uint16_t       ds2_state = ds2_read();
    comm_command_t command   = COMM_STOP;

    if (ds2_state == STOP)
    {
        return command;
    }

    uint8_t        i = 0;
    comm_command_t temp_cmd;
    for (i = 0; i < 18; i++)
    {
        if (ds2_state == command_map[i])
        {
            command = (comm_command_t)i;
            break;
        }
    }

    return command;
}

#endif
