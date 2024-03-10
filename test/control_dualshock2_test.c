#include "control.h"
#include "dualshock2.h"
#include "unity_config.h"
#include <stdint.h>
#include <unity/unity.h>

typedef struct
{
    uint8_t  initialized;
    uint16_t buttons;
} ds2_state_t;

ds2_state_t ds2_state = {};

void
dualshock2_init(void)
{
    ds2_state.initialized = 1;
}

uint16_t
dualshock2_read(void)
{
    return ds2_state.buttons;
}

void
setUp()
{
    ds2_state.initialized = 0;
    ds2_state.buttons     = DS2_NONE;
}

void
tearDown()
{
}

void
should_initialize_dualshock2(void)
{
    // when
    control_init();

    // then
    TEST_ASSERT_TRUE(ds2_state.initialized);
}

void
should_read_communication(control_command_t expected, uint16_t buttons)
{
    // given
    ds2_state.buttons = buttons;

    // when
    control_command_t actual = control_read();

    // then
    TEST_ASSERT_EQUAL(expected, actual);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_initialize_dualshock2);
    RUN_TEST(should_read_communication,
             CTRL_ROTATE_SIDE_RIGHT_FORWARD,
             DS2_UP | DS2_SQUARE);
    RUN_TEST(should_read_communication,
             CTRL_ROTATE_SIDE_LEFT_FORWARD,
             DS2_UP | DS2_CIRCLE);
    RUN_TEST(should_read_communication,
             CTRL_ROTATE_SIDE_RIGHT_BACKWARD,
             DS2_DOWN | DS2_SQUARE);
    RUN_TEST(should_read_communication,
             CTRL_ROTATE_SIDE_LEFT_BACKWARD,
             DS2_DOWN | DS2_CIRCLE);
    RUN_TEST(should_read_communication, CTRL_ROTATE_RIGHT, DS2_UP | DS2_CROSS);
    RUN_TEST(
        should_read_communication, CTRL_ROTATE_LEFT, DS2_DOWN | DS2_TRIANGLE);

    RUN_TEST(should_read_communication, CTRL_MOVE_FACE_FORWARD, DS2_UP);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_FACE_FORWARD,
             DS2_UP | DS2_TRIANGLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_FACE_FORWARD,
             DS2_UP | DS2_TRIANGLE | DS2_CIRCLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_FACE_FORWARD,
             DS2_UP | DS2_SQUARE | DS2_CROSS);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_FACE_FORWARD,
             DS2_UP | DS2_CROSS | DS2_SQUARE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_FACE_FORWARD,
             DS2_UP | DS2_SQUARE | DS2_TRIANGLE);

    RUN_TEST(should_read_communication, CTRL_MOVE_FACE_BACKWARD, DS2_DOWN);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_FACE_BACKWARD,
             DS2_DOWN | DS2_TRIANGLE | DS2_CIRCLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_FACE_BACKWARD,
             DS2_DOWN | DS2_CIRCLE | DS2_CROSS);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_FACE_BACKWARD,
             DS2_DOWN | DS2_CROSS);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_FACE_BACKWARD,
             DS2_DOWN | DS2_CROSS | DS2_SQUARE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_FACE_BACKWARD,
             DS2_DOWN | DS2_SQUARE | DS2_TRIANGLE);

    RUN_TEST(should_read_communication, CTRL_MOVE_SIDE_RIGHT, DS2_RIGHT);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_SIDE_RIGHT,
             DS2_RIGHT | DS2_TRIANGLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_SIDE_RIGHT,
             DS2_RIGHT | DS2_TRIANGLE | DS2_CIRCLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_SIDE_RIGHT,
             DS2_RIGHT | DS2_CIRCLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_SIDE_RIGHT,
             DS2_RIGHT | DS2_CIRCLE | DS2_CROSS);
    RUN_TEST(
        should_read_communication, CTRL_MOVE_SIDE_RIGHT, DS2_RIGHT | DS2_CROSS);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_SIDE_RIGHT,
             DS2_RIGHT | DS2_CROSS | DS2_SQUARE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_SIDE_RIGHT,
             DS2_RIGHT | DS2_SQUARE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_SIDE_RIGHT,
             DS2_RIGHT | DS2_SQUARE | DS2_TRIANGLE);

    RUN_TEST(should_read_communication, CTRL_MOVE_SIDE_LEFT, DS2_LEFT);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_SIDE_LEFT,
             DS2_LEFT | DS2_TRIANGLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_SIDE_LEFT,
             DS2_LEFT | DS2_TRIANGLE | DS2_CIRCLE);
    RUN_TEST(
        should_read_communication, CTRL_MOVE_SIDE_LEFT, DS2_LEFT | DS2_CIRCLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_SIDE_LEFT,
             DS2_LEFT | DS2_CIRCLE | DS2_CROSS);
    RUN_TEST(
        should_read_communication, CTRL_MOVE_SIDE_LEFT, DS2_LEFT | DS2_CROSS);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_SIDE_LEFT,
             DS2_LEFT | DS2_CROSS | DS2_SQUARE);
    RUN_TEST(
        should_read_communication, CTRL_MOVE_SIDE_LEFT, DS2_LEFT | DS2_SQUARE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_SIDE_LEFT,
             DS2_LEFT | DS2_SQUARE | DS2_TRIANGLE);

    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_RIGHT,
             DS2_UP | DS2_RIGHT);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_RIGHT,
             DS2_UP | DS2_RIGHT | DS2_TRIANGLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_RIGHT,
             DS2_UP | DS2_RIGHT | DS2_TRIANGLE | DS2_CIRCLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_RIGHT,
             DS2_UP | DS2_RIGHT | DS2_CIRCLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_RIGHT,
             DS2_UP | DS2_RIGHT | DS2_CIRCLE | DS2_CROSS);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_RIGHT,
             DS2_UP | DS2_RIGHT | DS2_CROSS);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_RIGHT,
             DS2_UP | DS2_RIGHT | DS2_CROSS | DS2_SQUARE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_RIGHT,
             DS2_UP | DS2_RIGHT | DS2_SQUARE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_RIGHT,
             DS2_UP | DS2_RIGHT | DS2_SQUARE | DS2_TRIANGLE);

    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_LEFT,
             DS2_UP | DS2_LEFT);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_LEFT,
             DS2_UP | DS2_LEFT | DS2_TRIANGLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_LEFT,
             DS2_UP | DS2_LEFT | DS2_TRIANGLE | DS2_CIRCLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_LEFT,
             DS2_UP | DS2_LEFT | DS2_CIRCLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_LEFT,
             DS2_UP | DS2_LEFT | DS2_CIRCLE | DS2_CROSS);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_LEFT,
             DS2_UP | DS2_LEFT | DS2_CROSS);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_LEFT,
             DS2_UP | DS2_LEFT | DS2_CROSS | DS2_SQUARE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_LEFT,
             DS2_UP | DS2_LEFT | DS2_SQUARE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_LEFT,
             DS2_UP | DS2_LEFT | DS2_SQUARE | DS2_TRIANGLE);

    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_DOWN | DS2_RIGHT);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_DOWN | DS2_RIGHT | DS2_TRIANGLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_DOWN | DS2_RIGHT | DS2_TRIANGLE | DS2_CIRCLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_DOWN | DS2_RIGHT | DS2_CIRCLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_DOWN | DS2_RIGHT | DS2_CIRCLE | DS2_CROSS);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_DOWN | DS2_RIGHT | DS2_CROSS);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_DOWN | DS2_RIGHT | DS2_CROSS | DS2_SQUARE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_DOWN | DS2_RIGHT | DS2_SQUARE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_DOWN | DS2_RIGHT | DS2_SQUARE | DS2_TRIANGLE);

    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_LEFT,
             DS2_DOWN | DS2_LEFT);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_LEFT,
             DS2_DOWN | DS2_LEFT | DS2_TRIANGLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_LEFT,
             DS2_DOWN | DS2_LEFT | DS2_TRIANGLE | DS2_CIRCLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_LEFT,
             DS2_DOWN | DS2_LEFT | DS2_CIRCLE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_LEFT,
             DS2_DOWN | DS2_LEFT | DS2_CIRCLE | DS2_CROSS);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_LEFT,
             DS2_DOWN | DS2_LEFT | DS2_CROSS);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_LEFT,
             DS2_DOWN | DS2_LEFT | DS2_CROSS | DS2_SQUARE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_LEFT,
             DS2_DOWN | DS2_LEFT | DS2_SQUARE);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_LEFT,
             DS2_DOWN | DS2_LEFT | DS2_SQUARE | DS2_TRIANGLE);

    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_RIGHT,
             DS2_UP | DS2_RIGHT);

    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_FORWARD_LEFT,
             DS2_UP | DS2_LEFT);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_DOWN | DS2_RIGHT);
    RUN_TEST(should_read_communication,
             CTRL_MOVE_DIAG_BACKWARD_LEFT,
             DS2_DOWN | DS2_LEFT);

    RUN_TEST(should_read_communication, CTRL_ROTATE_FACE_FRONT_RIGHT, DS2_R1);
    RUN_TEST(should_read_communication, CTRL_ROTATE_FACE_FRONT_LEFT, DS2_L1);
    RUN_TEST(should_read_communication, CTRL_ROTATE_FACE_REAR_RIGHT, DS2_R2);
    RUN_TEST(should_read_communication, CTRL_ROTATE_FACE_REAR_LEFT, DS2_L2);

    RUN_TEST(should_read_communication, CTRL_HARD_STOP, DS2_R1 | DS2_R2);
    RUN_TEST(should_read_communication, CTRL_HARD_STOP, DS2_R1 | DS2_L1);
    RUN_TEST(should_read_communication, CTRL_HARD_STOP, DS2_R1 | DS2_L2);
    RUN_TEST(should_read_communication, CTRL_HARD_STOP, DS2_R2 | DS2_L1);
    RUN_TEST(should_read_communication, CTRL_HARD_STOP, DS2_R2 | DS2_L2);
    RUN_TEST(should_read_communication, CTRL_HARD_STOP, DS2_L1 | DS2_L2)

    return UNITY_END();
}
