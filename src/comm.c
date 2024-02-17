#include "comm.h"
#include "irp.h"

void comm_init(void) { irp_init(); }

comm_command_t comm_read(void)
{
  irp_command_t irp_cmd = irp_read();
  switch (irp_cmd)
  {
    case IRP_CMD_2:
      return COMM_MOVE_FORWARD;
    case IRP_CMD_8:
      return COMM_MOVE_BACKWARD;
    case IRP_CMD_6:
      return COMM_TURN_RIGHT;
    case IRP_CMD_4:
      return COMM_TURN_LEFT;
    case IRP_CMD_FORWARD:
      return COMM_MOVE_RIGHT;
    case IRP_CMD_REWIND:
      return COMM_MOVE_LEFT;
    case IRP_CMD_3:
      return COMM_MOVE_FORWARD_RIGHT;
    case IRP_CMD_1:
      return COMM_MOVE_FORWARD_LEFT;
    case IRP_CMD_9:
      return COMM_MOVE_BACKWARD_RIGHT;
    case IRP_CMD_7:
      return COMM_MOVE_BACKWARD_LEFT;
    case IRP_CMD_PLUS:
      return COMM_ROTATE_RIGHT;
    case IRP_CMD_MINUS:
      return COMM_ROTATE_LEFT;
    case IRP_CMD_C:
      return COMM_FACE_RIGHT;
    case IRP_CMD_0:
      return COMM_FACE_LEFT;
    case IRP_CMD_BACK:
      return COMM_TURN_LEFT_BACKWARDS;
    default:
      return COMM_STAY;
  }
}