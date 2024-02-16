#include "comm.h"
#include "irp.h"

void comm_init(void) { irp_init(HAL_T1NRM_PRESC_1); }

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
    case IRP_CMD_1:
      return COMM_LEFT_FRONT_FORWARD;
    case IRP_CMD_3:
      return COMM_RIGHT_FRONT_BACKWARD;
    case IRP_CMD_9:
      return COMM_RIGHT_BACK_BACKWARD;
    case IRP_CMD_7:
      return COMM_LEFT_BACK_FORWARD;
    default:
      return COMM_STAY;
  }
}