#include "comm.h"
#include "motion.h"
#include <stdint.h>

static void apply(comm_command_t command);

static motion_t command_motion_matrix[19][4] = {
    [COMM_MOVE_FACE_FORWARD] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_FWD},
        },
    [COMM_MOVE_FACE_BACKWARD] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_BCK},
        },
    [COMM_MOVE_SIDE_RIGHT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_FWD},
        },
    [COMM_MOVE_SIDE_LEFT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_BCK},
        },
    [COMM_MOVE_DIAG_FORWARD_RIGHT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_FWD},
        },
    [COMM_MOVE_DIAG_FORWARD_LEFT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_STOP},
        },
    [COMM_MOVE_DIAG_BACKWARD_RIGHT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_STOP},
        },
    [COMM_MOVE_DIAG_BACKWARD_LEFT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_BCK},
        },
    [COMM_ROTATE_SIDE_RIGHT_FORWARD] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_FWD},
        },
    [COMM_ROTATE_SIDE_RIGHT_BACKWARD] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_BCK},
        },
    [COMM_ROTATE_SIDE_LEFT_FORWARD] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_STOP},
        },
    [COMM_ROTATE_SIDE_LEFT_BACKWARD] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_STOP},
        },
    [COMM_ROTATE_RIGHT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_FWD},
        },
    [COMM_ROTATE_LEFT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_BCK},
        },
    [COMM_ROTATE_FACE_FRONT_RIGHT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_STOP},
        },
    [COMM_ROTATE_FACE_FRONT_LEFT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_BCK},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_STOP},
        },
    [COMM_ROTATE_FACE_REAR_RIGHT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_BCK},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_FWD},
        },
    [COMM_ROTATE_FACE_REAR_LEFT] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_FWD},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_BCK},
        },
    [COMM_STOP] =
        {
            {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_STOP},
            {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_STOP},
        },
};

int main(void)
{
  motion_init();
  comm_init();

  while (1)
  {
    comm_command_t command = comm_read();
    apply(command);
  }

  return 0;
}

static void apply(comm_command_t command)
{
  for (uint8_t i = 0; i < 4; i++)
  {
    motion_set(&command_motion_matrix[command][i]);
  }

  if (command == COMM_STOP)
  {
    motion_stop();
  }
  else
  {
    motion_run();
  }
}
