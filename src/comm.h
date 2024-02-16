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
  COMM_LEFT_BACK_FORWARD,
  COMM_LEFT_FRONT_FORWARD,
  COMM_RIGHT_BACK_BACKWARD,
  COMM_RIGHT_FRONT_BACKWARD,
  COMM_STAY
} comm_command_t;

void comm_init(void);
comm_command_t comm_read(void);

#endif