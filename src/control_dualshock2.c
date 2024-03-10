#include "control.h"
#include "dualshock2.h"

static void
recognize_explicit_command(const uint16_t    *ds2_state,
                           control_command_t *command);

static void
recognize_main_motion(const uint16_t *ds2_state, control_command_t *command);

static void
recognize_hard_stop(const uint16_t *ds2_state, control_command_t *command);

static void
recognize_face_rotation(const uint16_t *ds2_state, control_command_t *command);

static uint16_t command_map[19] = {
    [CTRL_MOVE_FACE_FORWARD]          = DS2_UP,
    [CTRL_MOVE_FACE_BACKWARD]         = DS2_DOWN,
    [CTRL_MOVE_SIDE_RIGHT]            = DS2_RIGHT,
    [CTRL_MOVE_SIDE_LEFT]             = DS2_LEFT,
    [CTRL_MOVE_DIAG_FORWARD_RIGHT]    = DS2_UP | DS2_RIGHT,
    [CTRL_MOVE_DIAG_FORWARD_LEFT]     = DS2_UP | DS2_LEFT,
    [CTRL_MOVE_DIAG_BACKWARD_RIGHT]   = DS2_DOWN | DS2_RIGHT,
    [CTRL_MOVE_DIAG_BACKWARD_LEFT]    = DS2_DOWN | DS2_LEFT,
    [CTRL_ROTATE_SIDE_RIGHT_FORWARD]  = DS2_UP | DS2_SQUARE,
    [CTRL_ROTATE_SIDE_LEFT_FORWARD]   = DS2_UP | DS2_CIRCLE,
    [CTRL_ROTATE_SIDE_RIGHT_BACKWARD] = DS2_DOWN | DS2_SQUARE,
    [CTRL_ROTATE_SIDE_LEFT_BACKWARD]  = DS2_DOWN | DS2_CIRCLE,
    [CTRL_ROTATE_RIGHT]               = DS2_UP | DS2_CROSS,
    [CTRL_ROTATE_LEFT]                = DS2_DOWN | DS2_TRIANGLE,
    [CTRL_ROTATE_FACE_FRONT_RIGHT]    = DS2_R1,
    [CTRL_ROTATE_FACE_FRONT_LEFT]     = DS2_L1,
    [CTRL_ROTATE_FACE_REAR_RIGHT]     = DS2_R2,
    [CTRL_ROTATE_FACE_REAR_LEFT]      = DS2_L2,
};

static control_command_t explicit_commands[6] = {
    CTRL_ROTATE_SIDE_RIGHT_FORWARD,
    CTRL_ROTATE_SIDE_LEFT_FORWARD,
    CTRL_ROTATE_SIDE_RIGHT_BACKWARD,
    CTRL_ROTATE_SIDE_LEFT_BACKWARD,
    CTRL_ROTATE_RIGHT,
    CTRL_ROTATE_LEFT,
};

// order matters!
static control_command_t main_motion_commands[8] = {
    CTRL_MOVE_DIAG_FORWARD_RIGHT,
    CTRL_MOVE_DIAG_FORWARD_LEFT,
    CTRL_MOVE_DIAG_BACKWARD_RIGHT,
    CTRL_MOVE_DIAG_BACKWARD_LEFT,
    CTRL_MOVE_FACE_FORWARD,
    CTRL_MOVE_FACE_BACKWARD,
    CTRL_MOVE_SIDE_RIGHT,
    CTRL_MOVE_SIDE_LEFT,
};

void
control_init(void)
{
    dualshock2_init();
}

control_command_t
control_read(void)
{
    uint16_t          ds2_state = dualshock2_read();
    control_command_t command   = CTRL_SOFT_STOP;

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
recognize_main_motion(const uint16_t *ds2_state, control_command_t *command)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        control_command_t main_motion = main_motion_commands[i];
        if ((*ds2_state & command_map[main_motion]) == command_map[main_motion])
        {
            *command = main_motion;
            break;
        }
    }
}

static void
recognize_explicit_command(const uint16_t    *ds2_state,
                           control_command_t *command)
{
    for (uint8_t i = 0; i < 6; i++)
    {
        control_command_t explicit_command = explicit_commands[i];
        if (*ds2_state == command_map[explicit_command])
        {
            *command = explicit_command;
            break;
        }
    }
}

static void
recognize_hard_stop(const uint16_t *ds2_state, control_command_t *command)
{
    if (*ds2_state & (DS2_L1 | DS2_L2 | DS2_R1 | DS2_R2))
    {
        *command = CTRL_HARD_STOP;
    }
}

static void
recognize_face_rotation(const uint16_t *ds2_state, control_command_t *command)
{
    if ((*ds2_state & DS2_R1) && !(*ds2_state & (DS2_R2 | DS2_L1 | DS2_L2)))
    {
        *command = CTRL_ROTATE_FACE_FRONT_RIGHT;
    }

    if ((*ds2_state & DS2_L1) && !(*ds2_state & (DS2_L2 | DS2_R1 | DS2_R2)))
    {
        *command = CTRL_ROTATE_FACE_FRONT_LEFT;
    }

    if ((*ds2_state & DS2_R2) && !(*ds2_state & (DS2_R1 | DS2_L1 | DS2_L2)))
    {
        *command = CTRL_ROTATE_FACE_REAR_RIGHT;
    }

    if ((*ds2_state & DS2_L2) && !(*ds2_state & (DS2_R1 | DS2_R2 | DS2_L1)))
    {
        *command = CTRL_ROTATE_FACE_REAR_LEFT;
    }
}
