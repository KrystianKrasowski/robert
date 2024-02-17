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
  COMM_STAY
} comm_command_t;

void comm_init(void);
comm_command_t comm_read(void);

#endif