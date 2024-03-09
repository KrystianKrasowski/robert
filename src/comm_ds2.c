#ifndef M_COMM
#endif
#define M_COMM 2

#include "comm.h"

#if M_COMM == 2
#include "ds2.h"

static void
recognize_explicit_command(const uint16_t *ds2_state, comm_command_t *command);

static void
recognize_main_motion(const uint16_t *ds2_state, comm_command_t *command);

static void
recognize_hard_stop(const uint16_t *ds2_state, comm_command_t *command);

static void
recognize_face_rotation(const uint16_t *ds2_state, comm_command_t *command);

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

// order matters!
static comm_command_t main_motion_commands[8] = {
    COMM_MOVE_DIAG_FORWARD_RIGHT,
    COMM_MOVE_DIAG_FORWARD_LEFT,
    COMM_MOVE_DIAG_BACKWARD_RIGHT,
    COMM_MOVE_DIAG_BACKWARD_LEFT,
    COMM_MOVE_FACE_FORWARD,
    COMM_MOVE_FACE_BACKWARD,
    COMM_MOVE_SIDE_RIGHT,
    COMM_MOVE_SIDE_LEFT,
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
    comm_command_t command   = COMM_SOFT_STOP;

    if (ds2_state == DS2_NONE)
    {
        return command;
    }

    recognize_main_motion(&ds2_state, &command);
    recognize_explicit_command(&ds2_state, &command);
    recognize_hard_stop(&ds2_state, &command);
    recognize_face_rotation(&ds2_state, &command);

    return command;
}

static void
recognize_main_motion(const uint16_t *ds2_state, comm_command_t *command)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        comm_command_t main_motion = main_motion_commands[i];
        if ((*ds2_state & command_map[main_motion]) == command_map[main_motion])
        {
            *command = main_motion;
            break;
        }
    }
}

static void
recognize_explicit_command(const uint16_t *ds2_state, comm_command_t *command)
{
    for (uint8_t i = 0; i < 6; i++)
    {
        comm_command_t explicit_command = explicit_commands[i];
        if (*ds2_state == command_map[explicit_command])
        {
            *command = explicit_command;
            break;
        }
    }
}

static void
recognize_hard_stop(const uint16_t *ds2_state, comm_command_t *command)
{
    if (*ds2_state &
        (DS2_BUTTON_L1 | DS2_BUTTON_L2 | DS2_BUTTON_R1 | DS2_BUTTON_R2))
    {
        *command = COMM_HARD_STOP;
    }
}

static void
recognize_face_rotation(const uint16_t *ds2_state, comm_command_t *command)
{
    if ((*ds2_state & DS2_BUTTON_R1) &&
        !(*ds2_state & (DS2_BUTTON_R2 | DS2_BUTTON_L1 | DS2_BUTTON_L2)))
    {
        *command = COMM_ROTATE_FACE_FRONT_RIGHT;
    }

    if ((*ds2_state & DS2_BUTTON_L1) &&
        !(*ds2_state & (DS2_BUTTON_L2 | DS2_BUTTON_R1 | DS2_BUTTON_R2)))
    {
        *command = COMM_ROTATE_FACE_FRONT_LEFT;
    }

    if ((*ds2_state & DS2_BUTTON_R2) &&
        !(*ds2_state & (DS2_BUTTON_R1 | DS2_BUTTON_L1 | DS2_BUTTON_L2)))
    {
        *command = COMM_ROTATE_FACE_REAR_RIGHT;
    }

    if ((*ds2_state & DS2_BUTTON_L2) &&
        !(*ds2_state & (DS2_BUTTON_R1 | DS2_BUTTON_R2 | DS2_BUTTON_L1)))
    {
        *command = COMM_ROTATE_FACE_REAR_LEFT;
    }
}

#endif
