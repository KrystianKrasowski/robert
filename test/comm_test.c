#include "comm.h"
#include "irp.h"
#include "unity_config.h"
#include <stdint.h>
#include <unity/unity.h>

static uint8_t irp_initialized = 0;
static irp_command_t irp_command = IRP_CMD_NREADY;

void irp_init(void) { irp_initialized = 1; }

irp_command_t irp_read() { return irp_command; }

void setUp() {}

void tearDown()
{
  irp_initialized = 0;
  irp_command = 0;
}

void should_initialize_communication(void)
{
  // when
  comm_init();

  // then
  TEST_ASSERT_TRUE(irp_initialized == 1);
}

void should_read_command(irp_command_t irp_cmd, comm_command_t expected_cmd)
{
  // given
  irp_command = irp_cmd;

  // when
  comm_command_t actual_cmd = comm_read();

  // then
  TEST_ASSERT_EQUAL(expected_cmd, actual_cmd);
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(should_initialize_communication);
  RUN_TEST(should_read_command, IRP_CMD_2, COMM_MOVE_FORWARD);
  RUN_TEST(should_read_command, IRP_CMD_8, COMM_MOVE_BACKWARD);
  RUN_TEST(should_read_command, IRP_CMD_6, COMM_TURN_RIGHT);
  RUN_TEST(should_read_command, IRP_CMD_4, COMM_TURN_LEFT);
  RUN_TEST(should_read_command, IRP_CMD_FORWARD, COMM_MOVE_RIGHT);
  RUN_TEST(should_read_command, IRP_CMD_REWIND, COMM_MOVE_LEFT);
  RUN_TEST(should_read_command, IRP_CMD_3, COMM_MOVE_FORWARD_RIGHT);
  RUN_TEST(should_read_command, IRP_CMD_1, COMM_MOVE_FORWARD_LEFT);
  RUN_TEST(should_read_command, IRP_CMD_9, COMM_MOVE_BACKWARD_RIGHT);
  RUN_TEST(should_read_command, IRP_CMD_7, COMM_MOVE_BACKWARD_LEFT);
  RUN_TEST(should_read_command, IRP_CMD_PLUS, COMM_ROTATE_RIGHT);
  RUN_TEST(should_read_command, IRP_CMD_MINUS, COMM_ROTATE_LEFT);
  RUN_TEST(should_read_command, IRP_CMD_C, COMM_FACE_RIGHT);
  RUN_TEST(should_read_command, IRP_CMD_0, COMM_FACE_LEFT);
  return UNITY_END();
}