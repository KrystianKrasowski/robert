#include "comm.h"
#include "mov.h"

static void apply(comm_command_t command);

int main(void)
{
  mov_init();
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
  switch (command)
  {
    case COMM_MOVE_FORWARD:
      mov_move_forward();
      break;
    case COMM_MOVE_BACKWARD:
      mov_move_backward();
      break;
    case COMM_MOVE_RIGHT:
      mov_move_right();
      break;
    case COMM_MOVE_LEFT:
      mov_move_left();
      break;
    case COMM_TURN_RIGHT:
      mov_turn_right();
      break;
    case COMM_TURN_LEFT:
      mov_turn_left();
      break;
    case COMM_MOVE_FORWARD_RIGHT:
      mov_move_forward_right();
      break;
    case COMM_MOVE_FORWARD_LEFT:
      mov_move_forward_left();
      break;
    case COMM_MOVE_BACKWARD_RIGHT:
      mov_move_backward_right();
      break;
    case COMM_MOVE_BACKWARD_LEFT:
      mov_move_backward_left();
      break;
    case COMM_ROTATE_RIGHT:
      mov_rotate_right();
      break;
    case COMM_ROTATE_LEFT:
      mov_rotate_left();
      break;
    case COMM_FACE_RIGHT:
      mov_face_right();
      break;
    case COMM_FACE_LEFT:
      mov_face_left();
      break;
    case COMM_TURN_LEFT_BACKWARDS:
      mov_turn_left_backwards();
      break;
    case COMM_STAY:
      mov_stay();
      break;
  }
}