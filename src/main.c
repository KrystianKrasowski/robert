#include "control.h"
#include "motion.h"
#include <stdint.h>

static void
apply(control_command_t command);

static motion_t command_motion_matrix[20][4] = {
    [CTRL_MOVE_FACE_FORWARD] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_FWD},
        },
    [CTRL_MOVE_FACE_BACKWARD] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_BCK},
        },
    [CTRL_MOVE_SIDE_RIGHT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_FWD},
        },
    [CTRL_MOVE_SIDE_LEFT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_BCK},
        },
    [CTRL_MOVE_DIAG_FORWARD_RIGHT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_FWD},
        },
    [CTRL_MOVE_DIAG_FORWARD_LEFT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_STOP},
        },
    [CTRL_MOVE_DIAG_BACKWARD_RIGHT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_STOP},
        },
    [CTRL_MOVE_DIAG_BACKWARD_LEFT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_BCK},
        },
    [CTRL_ROTATE_SIDE_RIGHT_FORWARD] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_FWD},
        },
    [CTRL_ROTATE_SIDE_RIGHT_BACKWARD] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_BCK},
        },
    [CTRL_ROTATE_SIDE_LEFT_FORWARD] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_STOP},
        },
    [CTRL_ROTATE_SIDE_LEFT_BACKWARD] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_STOP},
        },
    [CTRL_ROTATE_RIGHT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_FWD},
        },
    [CTRL_ROTATE_LEFT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_BCK},
        },
    [CTRL_ROTATE_FACE_FRONT_RIGHT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_STOP},
        },
    [CTRL_ROTATE_FACE_FRONT_LEFT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_STOP},
        },
    [CTRL_ROTATE_FACE_REAR_RIGHT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_FWD},
        },
    [CTRL_ROTATE_FACE_REAR_LEFT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_BCK},
        },
    [CTRL_SOFT_STOP] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_STOP},
        },
    [CTRL_HARD_STOP] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_STOP},
        },
};

int
main(void)
{
    motion_init();
    control_init();

    while (1)
    {
        control_command_t command = control_read();
        apply(command);
    }

    return 0;
}

static void
apply(control_command_t command)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        motion_set(&command_motion_matrix[command][i]);
    }

    if (command == CTRL_SOFT_STOP)
    {
        motion_stop_running();
    }
    else if (command == CTRL_HARD_STOP)
    {
        motion_stop();
    }
    else
    {
        motion_run();
    }
}
