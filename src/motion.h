#ifndef _MOTION_H
#define _MOTION_H

typedef enum
{
    MOTION_MOTOR_LEFT_FRONT,
    MOTION_MOTOR_LEFT_REAR,
    MOTION_MOTOR_RIGHT_FRONT,
    MOTION_MOTOR_RIGHT_REAR,
} motion_motor_t;

typedef enum
{
    MOTION_DIR_FWD,
    MOTION_DIR_BCK,
    MOTION_DIR_STOP,
} motion_dir_t;

typedef struct
{
    motion_motor_t motor;
    motion_dir_t   direction;
} motion_t;

void
motion_init(void);

void
motion_set(const motion_t *motion);

void
motion_run(void);

void
motion_stop_running(void);

void
motion_stop(void);

#endif
