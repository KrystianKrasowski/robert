#include "vehicle.h"
#include "command.h"
#include "motion.h"

static command_t last_command = COMMAND_SOFT_STOP;

static motion_t
vehicle_create_motion(command_t command);

void
vehicle_init(void)
{
    command_init();
    motion_init();
}

void
vehicle_run(void)
{
    command_t current_command = command_receive();

    if (last_command != current_command)
    {
        last_command = current_command;
        motion_t motion = vehicle_create_motion(current_command);
        bool is_soft_stop = current_command == COMMAND_SOFT_STOP;
        motion_apply(&motion, is_soft_stop);
    }
}

static motion_t
vehicle_create_motion(command_t command)
{
    motion_t motion;
    switch (command)
    {
        case COMMAND_MOVE_FACE_FORWARD:
            motion.left_front  = MOTION_FORWARD;
            motion.right_front = MOTION_FORWARD;
            motion.left_rear   = MOTION_FORWARD;
            motion.right_rear  = MOTION_FORWARD;
            break;

        case COMMAND_MOVE_FACE_BACKWARD:
            motion.left_front  = MOTION_BACKWARD;
            motion.right_front = MOTION_BACKWARD;
            motion.left_rear   = MOTION_BACKWARD;
            motion.right_rear  = MOTION_BACKWARD;
            break;

        case COMMAND_MOVE_SIDE_RIGHT:
            motion.left_front  = MOTION_FORWARD;
            motion.right_front = MOTION_BACKWARD;
            motion.left_rear   = MOTION_BACKWARD;
            motion.right_rear  = MOTION_FORWARD;
            break;

        case COMMAND_MOVE_SIDE_LEFT:
            motion.left_front  = MOTION_BACKWARD;
            motion.right_front = MOTION_FORWARD;
            motion.left_rear   = MOTION_FORWARD;
            motion.right_rear  = MOTION_BACKWARD;
            break;

        case COMMAND_MOVE_DIAG_FORWARD_RIGHT:
            motion.left_front  = MOTION_FORWARD;
            motion.right_front = MOTION_NONE;
            motion.left_rear   = MOTION_NONE;
            motion.right_rear  = MOTION_FORWARD;
            break;

        case COMMAND_MOVE_DIAG_FORWARD_LEFT:
            motion.left_front  = MOTION_NONE;
            motion.right_front = MOTION_FORWARD;
            motion.left_rear   = MOTION_FORWARD;
            motion.right_rear  = MOTION_NONE;
            break;

        case COMMAND_MOVE_DIAG_BACKWARD_RIGHT:
            motion.left_front  = MOTION_NONE;
            motion.right_front = MOTION_BACKWARD;
            motion.left_rear   = MOTION_BACKWARD;
            motion.right_rear  = MOTION_NONE;
            break;

        case COMMAND_MOVE_DIAG_BACKWARD_LEFT:
            motion.left_front  = MOTION_BACKWARD;
            motion.right_front = MOTION_NONE;
            motion.left_rear   = MOTION_NONE;
            motion.right_rear  = MOTION_BACKWARD;
            break;

        case COMMAND_ROTATE_SIDE_RIGHT_FORWARD:
            motion.left_front  = MOTION_NONE;
            motion.right_front = MOTION_FORWARD;
            motion.left_rear   = MOTION_NONE;
            motion.right_rear  = MOTION_FORWARD;
            break;

        case COMMAND_ROTATE_SIDE_RIGHT_BACKWARD:
            motion.left_front  = MOTION_NONE;
            motion.right_front = MOTION_BACKWARD;
            motion.left_rear   = MOTION_NONE;
            motion.right_rear  = MOTION_BACKWARD;
            break;

        case COMMAND_ROTATE_SIDE_LEFT_FORWARD:
            motion.left_front  = MOTION_FORWARD;
            motion.right_front = MOTION_NONE;
            motion.left_rear   = MOTION_FORWARD;
            motion.right_rear  = MOTION_NONE;
            break;

        case COMMAND_ROTATE_SIDE_LEFT_BACKWARD:
            motion.left_front  = MOTION_BACKWARD;
            motion.right_front = MOTION_NONE;
            motion.left_rear   = MOTION_BACKWARD;
            motion.right_rear  = MOTION_NONE;
            break;

        case COMMAND_ROTATE_RIGHT:
            motion.left_front  = MOTION_FORWARD;
            motion.right_front = MOTION_BACKWARD;
            motion.left_rear   = MOTION_FORWARD;
            motion.right_rear  = MOTION_BACKWARD;
            break;

        case COMMAND_ROTATE_LEFT:
            motion.left_front  = MOTION_BACKWARD;
            motion.right_front = MOTION_FORWARD;
            motion.left_rear   = MOTION_BACKWARD;
            motion.right_rear  = MOTION_FORWARD;
            break;

        case COMMAND_ROTATE_FACE_FRONT_RIGHT:
            motion.left_front  = MOTION_FORWARD;
            motion.right_front = MOTION_BACKWARD;
            motion.left_rear   = MOTION_NONE;
            motion.right_rear  = MOTION_NONE;
            break;

        case COMMAND_ROTATE_FACE_FRONT_LEFT:
            motion.left_front  = MOTION_BACKWARD;
            motion.right_front = MOTION_FORWARD;
            motion.left_rear   = MOTION_NONE;
            motion.right_rear  = MOTION_NONE;
            break;

        case COMMAND_ROTATE_FACE_REAR_RIGHT:
            motion.left_front  = MOTION_NONE;
            motion.right_front = MOTION_NONE;
            motion.left_rear   = MOTION_BACKWARD;
            motion.right_rear  = MOTION_FORWARD;
            break;

        case COMMAND_ROTATE_FACE_REAR_LEFT:
            motion.left_front  = MOTION_NONE;
            motion.right_front = MOTION_NONE;
            motion.left_rear   = MOTION_FORWARD;
            motion.right_rear  = MOTION_BACKWARD;
            break;

        case COMMAND_SOFT_STOP:
        case COMMAND_HARD_STOP:
        default:
            motion.left_front  = MOTION_NONE;
            motion.right_front = MOTION_NONE;
            motion.left_rear   = MOTION_NONE;
            motion.right_rear  = MOTION_NONE;
    }

    return motion;
}