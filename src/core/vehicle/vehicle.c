#include "vehicle.h"
#include "command.h"
#include "motion.h"

static command_t last_command = COMMAND_SOFT_STOP;

static void
set_motion(motion_t *motion, command_t command);

// void
// vehicle_init(vehicle_t *self)
// {
//     command_init();
// }

void
vehicle_run(vehicle_t *self)
{
    command_t current_command = command_receive();

    if (last_command != current_command)
    {
        last_command = current_command;
        set_motion(&self->motion, current_command);
        bool is_soft_stop = current_command == COMMAND_SOFT_STOP;
        motion_apply(&self->motion, is_soft_stop);
    }
}

static void
set_motion(motion_t *motion, command_t command)
{
    switch (command)
    {
        case COMMAND_MOVE_FACE_FORWARD:
            motion_set_left_front(motion, MOTION_FORWARD);
            motion_set_right_front(motion, MOTION_FORWARD);
            motion_set_left_rear(motion, MOTION_FORWARD);
            motion_set_right_rear(motion, MOTION_FORWARD);
            break;

        case COMMAND_MOVE_FACE_BACKWARD:
            motion_set_left_front(motion, MOTION_BACKWARD);
            motion_set_right_front(motion, MOTION_BACKWARD);
            motion_set_left_rear(motion, MOTION_BACKWARD);
            motion_set_right_rear(motion, MOTION_BACKWARD);
            break;

        case COMMAND_MOVE_SIDE_RIGHT:
            motion_set_left_front(motion, MOTION_FORWARD);
            motion_set_right_front(motion, MOTION_BACKWARD);
            motion_set_left_rear(motion, MOTION_BACKWARD);
            motion_set_right_rear(motion, MOTION_FORWARD);
            break;

        case COMMAND_MOVE_SIDE_LEFT:
            motion_set_left_front(motion, MOTION_BACKWARD);
            motion_set_right_front(motion, MOTION_FORWARD);
            motion_set_left_rear(motion, MOTION_FORWARD);
            motion_set_right_rear(motion, MOTION_BACKWARD);
            break;

        case COMMAND_MOVE_DIAG_FORWARD_RIGHT:
            motion_set_left_front(motion, MOTION_FORWARD);
            motion_set_right_front(motion, MOTION_NONE);
            motion_set_left_rear(motion, MOTION_NONE);
            motion_set_right_rear(motion, MOTION_FORWARD);
            break;

        case COMMAND_MOVE_DIAG_FORWARD_LEFT:
            motion_set_left_front(motion, MOTION_NONE);
            motion_set_right_front(motion, MOTION_FORWARD);
            motion_set_left_rear(motion, MOTION_FORWARD);
            motion_set_right_rear(motion, MOTION_NONE);
            break;

        case COMMAND_MOVE_DIAG_BACKWARD_RIGHT:
            motion_set_left_front(motion, MOTION_NONE);
            motion_set_right_front(motion, MOTION_BACKWARD);
            motion_set_left_rear(motion, MOTION_BACKWARD);
            motion_set_right_rear(motion, MOTION_NONE);
            break;

        case COMMAND_MOVE_DIAG_BACKWARD_LEFT:
            motion_set_left_front(motion, MOTION_BACKWARD);
            motion_set_right_front(motion, MOTION_NONE);
            motion_set_left_rear(motion, MOTION_NONE);
            motion_set_right_rear(motion, MOTION_BACKWARD);
            break;

        case COMMAND_ROTATE_SIDE_RIGHT_FORWARD:
            motion_set_left_front(motion, MOTION_NONE);
            motion_set_right_front(motion, MOTION_FORWARD);
            motion_set_left_rear(motion, MOTION_NONE);
            motion_set_right_rear(motion, MOTION_FORWARD);
            break;

        case COMMAND_ROTATE_SIDE_RIGHT_BACKWARD:
            motion_set_left_front(motion, MOTION_NONE);
            motion_set_right_front(motion, MOTION_BACKWARD);
            motion_set_left_rear(motion, MOTION_NONE);
            motion_set_right_rear(motion, MOTION_BACKWARD);
            break;

        case COMMAND_ROTATE_SIDE_LEFT_FORWARD:
            motion_set_left_front(motion, MOTION_FORWARD);
            motion_set_right_front(motion, MOTION_NONE);
            motion_set_left_rear(motion, MOTION_FORWARD);
            motion_set_right_rear(motion, MOTION_NONE);
            break;

        case COMMAND_ROTATE_SIDE_LEFT_BACKWARD:
            motion_set_left_front(motion, MOTION_BACKWARD);
            motion_set_right_front(motion, MOTION_NONE);
            motion_set_left_rear(motion, MOTION_BACKWARD);
            motion_set_right_rear(motion, MOTION_NONE);
            break;

        case COMMAND_ROTATE_RIGHT:
            motion_set_left_front(motion, MOTION_FORWARD);
            motion_set_right_front(motion, MOTION_BACKWARD);
            motion_set_left_rear(motion, MOTION_FORWARD);
            motion_set_right_rear(motion, MOTION_BACKWARD);
            break;

        case COMMAND_ROTATE_LEFT:
            motion_set_left_front(motion, MOTION_BACKWARD);
            motion_set_right_front(motion, MOTION_FORWARD);
            motion_set_left_rear(motion, MOTION_BACKWARD);
            motion_set_right_rear(motion, MOTION_FORWARD);
            break;

        case COMMAND_ROTATE_FACE_FRONT_RIGHT:
            motion_set_left_front(motion, MOTION_FORWARD);
            motion_set_right_front(motion, MOTION_BACKWARD);
            motion_set_left_rear(motion, MOTION_NONE);
            motion_set_right_rear(motion, MOTION_NONE);
            break;

        case COMMAND_ROTATE_FACE_FRONT_LEFT:
            motion_set_left_front(motion, MOTION_BACKWARD);
            motion_set_right_front(motion, MOTION_FORWARD);
            motion_set_left_rear(motion, MOTION_NONE);
            motion_set_right_rear(motion, MOTION_NONE);
            break;

        case COMMAND_ROTATE_FACE_REAR_RIGHT:
            motion_set_left_front(motion, MOTION_NONE);
            motion_set_right_front(motion, MOTION_NONE);
            motion_set_left_rear(motion, MOTION_BACKWARD);
            motion_set_right_rear(motion, MOTION_FORWARD);
            break;

        case COMMAND_ROTATE_FACE_REAR_LEFT:
            motion_set_left_front(motion, MOTION_NONE);
            motion_set_right_front(motion, MOTION_NONE);
            motion_set_left_rear(motion, MOTION_FORWARD);
            motion_set_right_rear(motion, MOTION_BACKWARD);
            break;

        case COMMAND_SOFT_STOP:
        case COMMAND_HARD_STOP:
        default:
            motion_set_left_front(motion, MOTION_NONE);
            motion_set_right_front(motion, MOTION_NONE);
            motion_set_left_rear(motion, MOTION_NONE);
            motion_set_right_rear(motion, MOTION_NONE);
    }
}