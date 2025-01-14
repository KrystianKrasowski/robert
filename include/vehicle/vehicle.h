#ifndef _VEHICLE_H
#define _VEHICLE_H

typedef enum
{
    COMMAND_MOVE_FACE_FORWARD,
    COMMAND_MOVE_FACE_BACKWARD,
    COMMAND_MOVE_SIDE_RIGHT,
    COMMAND_MOVE_SIDE_LEFT,
    COMMAND_MOVE_DIAG_FORWARD_RIGHT,
    COMMAND_MOVE_DIAG_FORWARD_LEFT,
    COMMAND_MOVE_DIAG_BACKWARD_RIGHT,
    COMMAND_MOVE_DIAG_BACKWARD_LEFT,
    COMMAND_ROTATE_SIDE_RIGHT_FORWARD,
    COMMAND_ROTATE_SIDE_LEFT_FORWARD,
    COMMAND_ROTATE_SIDE_RIGHT_BACKWARD,
    COMMAND_ROTATE_SIDE_LEFT_BACKWARD,
    COMMAND_ROTATE_RIGHT,
    COMMAND_ROTATE_LEFT,
    COMMAND_ROTATE_FACE_FRONT_RIGHT,
    COMMAND_ROTATE_FACE_FRONT_LEFT,
    COMMAND_ROTATE_FACE_REAR_RIGHT,
    COMMAND_ROTATE_FACE_REAR_LEFT,
    COMMAND_SOFT_STOP,
    COMMAND_HARD_STOP,
} vehicle_command_t;

typedef enum
{
    MOTION_FORWARD,
    MOTION_BACKWARD,
    MOTION_NONE,
} vehicle_motion_t;

typedef struct vehicle
{
    vehicle_command_t current_command;
    vehicle_motion_t motor_left_front;
    vehicle_motion_t motor_right_front;
    vehicle_motion_t motor_left_rear;
    vehicle_motion_t motor_right_rear;
} vehicle_t;

void
vehicle_init(vehicle_t *self);

void
vehicle_run(vehicle_t *self);

#endif