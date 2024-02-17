#ifndef _COMM
#define _COMM

typedef enum
{
  COMM_MOVE_FORWARD,
  COMM_MOVE_BACKWARD,
  COMM_MOVE_RIGHT,
  COMM_MOVE_LEFT,
  COMM_TURN_RIGHT,
  COMM_TURN_LEFT,
  COMM_MOVE_FORWARD_RIGHT,
  COMM_MOVE_FORWARD_LEFT,
  COMM_MOVE_BACKWARD_RIGHT,
  COMM_MOVE_BACKWARD_LEFT,
  COMM_ROTATE_RIGHT,
  COMM_ROTATE_LEFT,
  COMM_FACE_RIGHT,
  COMM_FACE_LEFT,
  COMM_TURN_LEFT_BACKWARDS,
  COMM_STAY
} comm_command_t;

void comm_init(void);
comm_command_t comm_read(void);

#endif