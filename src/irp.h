#ifndef _IRP
#define _IRP

#include <avrhal/t1int.h>
#include <avrhal/t1nrm.h>

#define IR_WIDTH_LOGIC_0 1400
#define IR_WIDTH_LOGIC_1 2500

typedef enum
{
  IRP_CMD_ON_OFF = 0xA2,
  IRP_CMD_MENU = 0xE2,
  IRP_CMD_TEST = 0x22,
  IRP_CMD_PLUS = 0x02,
  IRP_CMD_BACK = 0xC2,
  IRP_CMD_REWIND = 0xE0,
  IRP_CMD_PLAY = 0xA8,
  IRP_CMD_FORWARD = 0x90,
  IRP_CMD_0 = 0x68,
  IRP_CMD_MINUS = 0x98,
  IRP_CMD_C = 0xB0,
  IRP_CMD_1 = 0x30,
  IRP_CMD_2 = 0x18,
  IRP_CMD_3 = 0x7A,
  IRP_CMD_4 = 0x10,
  IRP_CMD_5 = 0x38,
  IRP_CMD_6 = 0x5A,
  IRP_CMD_7 = 0x42,
  IRP_CMD_8 = 0x4A,
  IRP_CMD_9 = 0x52,
  IRP_CMD_NREADY = 0
} irp_command_t;

void irp_init(hal_t1nrm_prescaller_t presc);
irp_command_t irp_read(void);
void irp_release(void);

#endif