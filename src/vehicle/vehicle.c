#include "vehicle.h"
#include "vehicle_command_port.h"
#include "vehicle_motion_port.h"

static void
vehicle_motors_set(vehicle_t *self);

void
vehicle_init(vehicle_t *self)
{
    vehicle_command_init();
    vehicle_motion_init();

    self->current_command   = COMMAND_SOFT_STOP;
    self->motor_left_front  = MOTION_NONE;
    self->motor_left_rear   = MOTION_NONE;
    self->motor_right_front = MOTION_NONE;
    self->motor_right_rear  = MOTION_NONE;
}

void
vehicle_run(vehicle_t *self)
{
    vehicle_command_receive(self);
    vehicle_motors_set(self);
    vehicle_motion_apply(self);
}

static void
vehicle_motors_set(vehicle_t *self)
{
    switch (self->current_command)
    {
        case COMMAND_MOVE_FACE_FORWARD:
            self->motor_left_front  = MOTION_FORWARD;
            self->motor_right_front = MOTION_FORWARD;
            self->motor_left_rear   = MOTION_FORWARD;
            self->motor_right_rear  = MOTION_FORWARD;
            break;

        case COMMAND_MOVE_FACE_BACKWARD:
            self->motor_left_front  = MOTION_BACKWARD;
            self->motor_right_front = MOTION_BACKWARD;
            self->motor_left_rear   = MOTION_BACKWARD;
            self->motor_right_rear  = MOTION_BACKWARD;
            break;

        case COMMAND_MOVE_SIDE_RIGHT:
            self->motor_left_front  = MOTION_FORWARD;
            self->motor_right_front = MOTION_BACKWARD;
            self->motor_left_rear   = MOTION_BACKWARD;
            self->motor_right_rear  = MOTION_FORWARD;
            break;

        case COMMAND_MOVE_SIDE_LEFT:
            self->motor_left_front  = MOTION_BACKWARD;
            self->motor_right_front = MOTION_FORWARD;
            self->motor_left_rear   = MOTION_FORWARD;
            self->motor_right_rear  = MOTION_BACKWARD;
            break;

        case COMMAND_MOVE_DIAG_FORWARD_RIGHT:
            self->motor_left_front  = MOTION_FORWARD;
            self->motor_right_front = MOTION_NONE;
            self->motor_left_rear   = MOTION_NONE;
            self->motor_right_rear  = MOTION_FORWARD;
            break;

        case COMMAND_MOVE_DIAG_FORWARD_LEFT:
            self->motor_left_front  = MOTION_NONE;
            self->motor_right_front = MOTION_FORWARD;
            self->motor_left_rear   = MOTION_FORWARD;
            self->motor_right_rear  = MOTION_NONE;
            break;

        case COMMAND_MOVE_DIAG_BACKWARD_RIGHT:
            self->motor_left_front  = MOTION_NONE;
            self->motor_right_front = MOTION_BACKWARD;
            self->motor_left_rear   = MOTION_BACKWARD;
            self->motor_right_rear  = MOTION_NONE;
            break;

        case COMMAND_MOVE_DIAG_BACKWARD_LEFT:
            self->motor_left_front  = MOTION_BACKWARD;
            self->motor_right_front = MOTION_NONE;
            self->motor_left_rear   = MOTION_NONE;
            self->motor_right_rear  = MOTION_BACKWARD;
            break;

        case COMMAND_ROTATE_SIDE_RIGHT_FORWARD:
            self->motor_left_front  = MOTION_NONE;
            self->motor_right_front = MOTION_FORWARD;
            self->motor_left_rear   = MOTION_NONE;
            self->motor_right_rear  = MOTION_FORWARD;
            break;

        case COMMAND_ROTATE_SIDE_RIGHT_BACKWARD:
            self->motor_left_front  = MOTION_NONE;
            self->motor_right_front = MOTION_BACKWARD;
            self->motor_left_rear   = MOTION_NONE;
            self->motor_right_rear  = MOTION_BACKWARD;
            break;

        case COMMAND_ROTATE_SIDE_LEFT_FORWARD:
            self->motor_left_front  = MOTION_FORWARD;
            self->motor_right_front = MOTION_NONE;
            self->motor_left_rear   = MOTION_FORWARD;
            self->motor_right_rear  = MOTION_NONE;
            break;

        case COMMAND_ROTATE_SIDE_LEFT_BACKWARD:
            self->motor_left_front  = MOTION_BACKWARD;
            self->motor_right_front = MOTION_NONE;
            self->motor_left_rear   = MOTION_BACKWARD;
            self->motor_right_rear  = MOTION_NONE;
            break;

        case COMMAND_ROTATE_RIGHT:
            self->motor_left_front  = MOTION_FORWARD;
            self->motor_right_front = MOTION_BACKWARD;
            self->motor_left_rear   = MOTION_FORWARD;
            self->motor_right_rear  = MOTION_BACKWARD;
            break;

        case COMMAND_ROTATE_LEFT:
            self->motor_left_front  = MOTION_BACKWARD;
            self->motor_right_front = MOTION_FORWARD;
            self->motor_left_rear   = MOTION_BACKWARD;
            self->motor_right_rear  = MOTION_FORWARD;
            break;

        case COMMAND_ROTATE_FACE_FRONT_RIGHT:
            self->motor_left_front  = MOTION_FORWARD;
            self->motor_right_front = MOTION_BACKWARD;
            self->motor_left_rear   = MOTION_NONE;
            self->motor_right_rear  = MOTION_NONE;
            break;

        case COMMAND_ROTATE_FACE_FRONT_LEFT:
            self->motor_left_front  = MOTION_BACKWARD;
            self->motor_right_front = MOTION_FORWARD;
            self->motor_left_rear   = MOTION_NONE;
            self->motor_right_rear  = MOTION_NONE;
            break;

        case COMMAND_ROTATE_FACE_REAR_RIGHT:
            self->motor_left_front  = MOTION_NONE;
            self->motor_right_front = MOTION_NONE;
            self->motor_left_rear   = MOTION_BACKWARD;
            self->motor_right_rear  = MOTION_FORWARD;
            break;

        case COMMAND_ROTATE_FACE_REAR_LEFT:
            self->motor_left_front  = MOTION_NONE;
            self->motor_right_front = MOTION_NONE;
            self->motor_left_rear   = MOTION_FORWARD;
            self->motor_right_rear  = MOTION_BACKWARD;
            break;

        case COMMAND_SOFT_STOP:
        case COMMAND_HARD_STOP:
        default:
            self->motor_left_front  = MOTION_NONE;
            self->motor_right_front = MOTION_NONE;
            self->motor_left_rear   = MOTION_NONE;
            self->motor_right_rear  = MOTION_NONE;
    }
}