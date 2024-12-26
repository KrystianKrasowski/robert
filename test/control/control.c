#include "control.h"
#include "dualshock2.h"
#include "unity.h"
#include "unity_config.h"
#include <stdbool.h>

static bool dualshock2_initialized = false;

static uint16_t dualshock2_state = DS2_NONE;

void
dualshock2_init(void)
{
    dualshock2_initialized = true;
}

uint16_t
dualshock2_read(void)
{
    return dualshock2_state;
}

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_initialize_dualshock2_controller()
{
    // when
    control_init();

    // then
    TEST_ASSERT_TRUE(dualshock2_initialized);
}

void
should_read_command(uint16_t given_dualshock2_state, control_command_t expected)
{
    // given
    dualshock2_state = given_dualshock2_state;

    // when
    control_command_t actual = control_read();

    // then
    TEST_ASSERT_EQUAL(expected, actual);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_TEST(should_initialize_dualshock2_controller);
    
    RUN_PARAM_TEST(should_read_command, DS2_UP, CTRL_MOVE_FACE_FORWARD);
    RUN_PARAM_TEST(should_read_command, DS2_DOWN, CTRL_MOVE_FACE_BACKWARD);
    RUN_PARAM_TEST(should_read_command, DS2_RIGHT, CTRL_MOVE_SIDE_RIGHT);
    RUN_PARAM_TEST(should_read_command, DS2_LEFT, CTRL_MOVE_SIDE_LEFT);
    RUN_PARAM_TEST(should_read_command, DS2_UP | DS2_RIGHT, CTRL_MOVE_DIAG_FORWARD_RIGHT);
    RUN_PARAM_TEST(should_read_command, DS2_UP | DS2_LEFT, CTRL_MOVE_DIAG_FORWARD_LEFT);
    RUN_PARAM_TEST(should_read_command, DS2_DOWN | DS2_RIGHT, CTRL_MOVE_DIAG_BACKWARD_RIGHT);
    RUN_PARAM_TEST(should_read_command, DS2_DOWN | DS2_LEFT, CTRL_MOVE_DIAG_BACKWARD_LEFT);
    RUN_PARAM_TEST(should_read_command, DS2_UP | DS2_SQUARE, CTRL_ROTATE_SIDE_RIGHT_FORWARD);
    RUN_PARAM_TEST(should_read_command, DS2_UP | DS2_CIRCLE, CTRL_ROTATE_SIDE_LEFT_FORWARD);
    RUN_PARAM_TEST(should_read_command, DS2_DOWN | DS2_SQUARE, CTRL_ROTATE_SIDE_RIGHT_BACKWARD);
    RUN_PARAM_TEST(should_read_command, DS2_DOWN | DS2_CIRCLE, CTRL_ROTATE_SIDE_LEFT_BACKWARD);
    RUN_PARAM_TEST(should_read_command, DS2_UP | DS2_CROSS, CTRL_ROTATE_RIGHT);
    RUN_PARAM_TEST(should_read_command, DS2_DOWN | DS2_TRIANGLE, CTRL_ROTATE_LEFT);
    RUN_PARAM_TEST(should_read_command, DS2_R1, CTRL_ROTATE_FACE_FRONT_RIGHT);
    RUN_PARAM_TEST(should_read_command, DS2_L1, CTRL_ROTATE_FACE_FRONT_LEFT);
    RUN_PARAM_TEST(should_read_command, DS2_R2, CTRL_ROTATE_FACE_REAR_RIGHT);
    RUN_PARAM_TEST(should_read_command, DS2_L2, CTRL_ROTATE_FACE_REAR_LEFT);

    return UNITY_END();
}