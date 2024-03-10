#include "control.h"
#include "infrared_pilot.h"
#include "unity_config.h"
#include <stdint.h>
#include <unity/unity.h>

static uint8_t                  irp_initialized = 0;
static infrared_pilot_command_t irp_command     = IRP_CMD_NREADY;

void
infrared_pilot_init(void)
{
    irp_initialized = 1;
}

infrared_pilot_command_t
infrared_pilot_read()
{
    return irp_command;
}

void
setUp()
{
}

void
tearDown()
{
    irp_initialized = 0;
    irp_command     = 0;
}

void
should_initialize_communication(void)
{
    // when
    control_init();

    // then
    TEST_ASSERT_TRUE(irp_initialized == 1);
}

void
should_read_command(infrared_pilot_command_t irp_cmd,
                    control_command_t        expected_cmd)
{
    // given
    irp_command = irp_cmd;

    // when
    control_command_t actual_cmd = control_read();

    // then
    TEST_ASSERT_EQUAL(expected_cmd, actual_cmd);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_initialize_communication);
    RUN_TEST(should_read_command, IRP_CMD_2, CTRL_MOVE_FACE_FORWARD);
    RUN_TEST(should_read_command, IRP_CMD_8, CTRL_MOVE_FACE_BACKWARD);
    RUN_TEST(should_read_command, IRP_CMD_6, CTRL_ROTATE_SIDE_LEFT_FORWARD);
    RUN_TEST(should_read_command, IRP_CMD_4, CTRL_ROTATE_SIDE_RIGHT_FORWARD);
    RUN_TEST(should_read_command, IRP_CMD_FORWARD, CTRL_MOVE_SIDE_RIGHT);
    RUN_TEST(should_read_command, IRP_CMD_REWIND, CTRL_MOVE_SIDE_LEFT);
    RUN_TEST(should_read_command, IRP_CMD_3, CTRL_MOVE_DIAG_FORWARD_RIGHT);
    RUN_TEST(should_read_command, IRP_CMD_1, CTRL_MOVE_DIAG_FORWARD_LEFT);
    RUN_TEST(should_read_command, IRP_CMD_9, CTRL_MOVE_DIAG_BACKWARD_RIGHT);
    RUN_TEST(should_read_command, IRP_CMD_7, CTRL_MOVE_DIAG_BACKWARD_LEFT);
    RUN_TEST(should_read_command, IRP_CMD_PLUS, CTRL_ROTATE_RIGHT);
    RUN_TEST(should_read_command, IRP_CMD_MINUS, CTRL_ROTATE_LEFT);
    RUN_TEST(should_read_command, IRP_CMD_C, CTRL_ROTATE_FACE_FRONT_RIGHT);
    RUN_TEST(should_read_command, IRP_CMD_0, CTRL_ROTATE_FACE_FRONT_LEFT);
    return UNITY_END();
}
