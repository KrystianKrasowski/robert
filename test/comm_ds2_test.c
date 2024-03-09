#include "comm.h"
#include "ds2.h"
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
ds2_init(void)
{
    ds2_state.initialized = 1;
}

uint16_t
ds2_read(void)
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
    comm_init();

    // then
    TEST_ASSERT_TRUE(ds2_state.initialized);
}

void
should_read_communication(comm_command_t expected, uint16_t buttons)
{
    // given
    ds2_state.buttons = buttons;

    // when
    comm_command_t actual = comm_read();

    // then
    TEST_ASSERT_EQUAL(expected, actual);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_initialize_dualshock2);
    RUN_TEST(should_read_communication,
             COMM_ROTATE_SIDE_RIGHT_FORWARD,
             DS2_BUTTON_UP | DS2_BUTTON_SQUARE);
    RUN_TEST(should_read_communication,
             COMM_ROTATE_SIDE_LEFT_FORWARD,
             DS2_BUTTON_UP | DS2_BUTTON_CIRCLE);
    RUN_TEST(should_read_communication,
             COMM_ROTATE_SIDE_RIGHT_BACKWARD,
             DS2_BUTTON_DOWN | DS2_BUTTON_SQUARE);
    RUN_TEST(should_read_communication,
             COMM_ROTATE_SIDE_LEFT_BACKWARD,
             DS2_BUTTON_DOWN | DS2_BUTTON_CIRCLE);
    RUN_TEST(should_read_communication,
             COMM_ROTATE_RIGHT,
             DS2_BUTTON_UP | DS2_BUTTON_CROSS);
    RUN_TEST(should_read_communication,
             COMM_ROTATE_LEFT,
             DS2_BUTTON_DOWN | DS2_BUTTON_TRIANGLE);

    RUN_TEST(should_read_communication, COMM_MOVE_FACE_FORWARD, DS2_BUTTON_UP);
    RUN_TEST(should_read_communication,
             COMM_MOVE_FACE_FORWARD,
             DS2_BUTTON_UP | DS2_BUTTON_TRIANGLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_FACE_FORWARD,
             DS2_BUTTON_UP | DS2_BUTTON_TRIANGLE | DS2_BUTTON_CIRCLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_FACE_FORWARD,
             DS2_BUTTON_UP | DS2_BUTTON_SQUARE | DS2_BUTTON_CROSS);
    RUN_TEST(should_read_communication,
             COMM_MOVE_FACE_FORWARD,
             DS2_BUTTON_UP | DS2_BUTTON_CROSS | DS2_BUTTON_SQUARE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_FACE_FORWARD,
             DS2_BUTTON_UP | DS2_BUTTON_SQUARE | DS2_BUTTON_TRIANGLE);

    RUN_TEST(
        should_read_communication, COMM_MOVE_FACE_BACKWARD, DS2_BUTTON_DOWN);
    RUN_TEST(should_read_communication,
             COMM_MOVE_FACE_BACKWARD,
             DS2_BUTTON_DOWN | DS2_BUTTON_TRIANGLE | DS2_BUTTON_CIRCLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_FACE_BACKWARD,
             DS2_BUTTON_DOWN | DS2_BUTTON_CIRCLE | DS2_BUTTON_CROSS);
    RUN_TEST(should_read_communication,
             COMM_MOVE_FACE_BACKWARD,
             DS2_BUTTON_DOWN | DS2_BUTTON_CROSS);
    RUN_TEST(should_read_communication,
             COMM_MOVE_FACE_BACKWARD,
             DS2_BUTTON_DOWN | DS2_BUTTON_CROSS | DS2_BUTTON_SQUARE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_FACE_BACKWARD,
             DS2_BUTTON_DOWN | DS2_BUTTON_SQUARE | DS2_BUTTON_TRIANGLE);

    RUN_TEST(should_read_communication, COMM_MOVE_SIDE_RIGHT, DS2_BUTTON_RIGHT);
    RUN_TEST(should_read_communication,
             COMM_MOVE_SIDE_RIGHT,
             DS2_BUTTON_RIGHT | DS2_BUTTON_TRIANGLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_SIDE_RIGHT,
             DS2_BUTTON_RIGHT | DS2_BUTTON_TRIANGLE | DS2_BUTTON_CIRCLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_SIDE_RIGHT,
             DS2_BUTTON_RIGHT | DS2_BUTTON_CIRCLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_SIDE_RIGHT,
             DS2_BUTTON_RIGHT | DS2_BUTTON_CIRCLE | DS2_BUTTON_CROSS);
    RUN_TEST(should_read_communication,
             COMM_MOVE_SIDE_RIGHT,
             DS2_BUTTON_RIGHT | DS2_BUTTON_CROSS);
    RUN_TEST(should_read_communication,
             COMM_MOVE_SIDE_RIGHT,
             DS2_BUTTON_RIGHT | DS2_BUTTON_CROSS | DS2_BUTTON_SQUARE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_SIDE_RIGHT,
             DS2_BUTTON_RIGHT | DS2_BUTTON_SQUARE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_SIDE_RIGHT,
             DS2_BUTTON_RIGHT | DS2_BUTTON_SQUARE | DS2_BUTTON_TRIANGLE);

    RUN_TEST(should_read_communication, COMM_MOVE_SIDE_LEFT, DS2_BUTTON_LEFT);
    RUN_TEST(should_read_communication,
             COMM_MOVE_SIDE_LEFT,
             DS2_BUTTON_LEFT | DS2_BUTTON_TRIANGLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_SIDE_LEFT,
             DS2_BUTTON_LEFT | DS2_BUTTON_TRIANGLE | DS2_BUTTON_CIRCLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_SIDE_LEFT,
             DS2_BUTTON_LEFT | DS2_BUTTON_CIRCLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_SIDE_LEFT,
             DS2_BUTTON_LEFT | DS2_BUTTON_CIRCLE | DS2_BUTTON_CROSS);
    RUN_TEST(should_read_communication,
             COMM_MOVE_SIDE_LEFT,
             DS2_BUTTON_LEFT | DS2_BUTTON_CROSS);
    RUN_TEST(should_read_communication,
             COMM_MOVE_SIDE_LEFT,
             DS2_BUTTON_LEFT | DS2_BUTTON_CROSS | DS2_BUTTON_SQUARE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_SIDE_LEFT,
             DS2_BUTTON_LEFT | DS2_BUTTON_SQUARE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_SIDE_LEFT,
             DS2_BUTTON_LEFT | DS2_BUTTON_SQUARE | DS2_BUTTON_TRIANGLE);

    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_RIGHT,
             DS2_BUTTON_UP | DS2_BUTTON_RIGHT);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_RIGHT,
             DS2_BUTTON_UP | DS2_BUTTON_RIGHT | DS2_BUTTON_TRIANGLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_RIGHT,
             DS2_BUTTON_UP | DS2_BUTTON_RIGHT | DS2_BUTTON_TRIANGLE |
                 DS2_BUTTON_CIRCLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_RIGHT,
             DS2_BUTTON_UP | DS2_BUTTON_RIGHT | DS2_BUTTON_CIRCLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_RIGHT,
             DS2_BUTTON_UP | DS2_BUTTON_RIGHT | DS2_BUTTON_CIRCLE |
                 DS2_BUTTON_CROSS);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_RIGHT,
             DS2_BUTTON_UP | DS2_BUTTON_RIGHT | DS2_BUTTON_CROSS);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_RIGHT,
             DS2_BUTTON_UP | DS2_BUTTON_RIGHT | DS2_BUTTON_CROSS |
                 DS2_BUTTON_SQUARE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_RIGHT,
             DS2_BUTTON_UP | DS2_BUTTON_RIGHT | DS2_BUTTON_SQUARE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_RIGHT,
             DS2_BUTTON_UP | DS2_BUTTON_RIGHT | DS2_BUTTON_SQUARE |
                 DS2_BUTTON_TRIANGLE);

    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_LEFT,
             DS2_BUTTON_UP | DS2_BUTTON_LEFT);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_LEFT,
             DS2_BUTTON_UP | DS2_BUTTON_LEFT | DS2_BUTTON_TRIANGLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_LEFT,
             DS2_BUTTON_UP | DS2_BUTTON_LEFT | DS2_BUTTON_TRIANGLE |
                 DS2_BUTTON_CIRCLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_LEFT,
             DS2_BUTTON_UP | DS2_BUTTON_LEFT | DS2_BUTTON_CIRCLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_LEFT,
             DS2_BUTTON_UP | DS2_BUTTON_LEFT | DS2_BUTTON_CIRCLE |
                 DS2_BUTTON_CROSS);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_LEFT,
             DS2_BUTTON_UP | DS2_BUTTON_LEFT | DS2_BUTTON_CROSS);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_LEFT,
             DS2_BUTTON_UP | DS2_BUTTON_LEFT | DS2_BUTTON_CROSS |
                 DS2_BUTTON_SQUARE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_LEFT,
             DS2_BUTTON_UP | DS2_BUTTON_LEFT | DS2_BUTTON_SQUARE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_LEFT,
             DS2_BUTTON_UP | DS2_BUTTON_LEFT | DS2_BUTTON_SQUARE |
                 DS2_BUTTON_TRIANGLE);

    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_BUTTON_DOWN | DS2_BUTTON_RIGHT);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_BUTTON_DOWN | DS2_BUTTON_RIGHT | DS2_BUTTON_TRIANGLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_BUTTON_DOWN | DS2_BUTTON_RIGHT | DS2_BUTTON_TRIANGLE |
                 DS2_BUTTON_CIRCLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_BUTTON_DOWN | DS2_BUTTON_RIGHT | DS2_BUTTON_CIRCLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_BUTTON_DOWN | DS2_BUTTON_RIGHT | DS2_BUTTON_CIRCLE |
                 DS2_BUTTON_CROSS);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_BUTTON_DOWN | DS2_BUTTON_RIGHT | DS2_BUTTON_CROSS);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_BUTTON_DOWN | DS2_BUTTON_RIGHT | DS2_BUTTON_CROSS |
                 DS2_BUTTON_SQUARE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_BUTTON_DOWN | DS2_BUTTON_RIGHT | DS2_BUTTON_SQUARE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_BUTTON_DOWN | DS2_BUTTON_RIGHT | DS2_BUTTON_SQUARE |
                 DS2_BUTTON_TRIANGLE);

    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_LEFT,
             DS2_BUTTON_DOWN | DS2_BUTTON_LEFT);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_LEFT,
             DS2_BUTTON_DOWN | DS2_BUTTON_LEFT | DS2_BUTTON_TRIANGLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_LEFT,
             DS2_BUTTON_DOWN | DS2_BUTTON_LEFT | DS2_BUTTON_TRIANGLE |
                 DS2_BUTTON_CIRCLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_LEFT,
             DS2_BUTTON_DOWN | DS2_BUTTON_LEFT | DS2_BUTTON_CIRCLE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_LEFT,
             DS2_BUTTON_DOWN | DS2_BUTTON_LEFT | DS2_BUTTON_CIRCLE |
                 DS2_BUTTON_CROSS);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_LEFT,
             DS2_BUTTON_DOWN | DS2_BUTTON_LEFT | DS2_BUTTON_CROSS);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_LEFT,
             DS2_BUTTON_DOWN | DS2_BUTTON_LEFT | DS2_BUTTON_CROSS |
                 DS2_BUTTON_SQUARE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_LEFT,
             DS2_BUTTON_DOWN | DS2_BUTTON_LEFT | DS2_BUTTON_SQUARE);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_LEFT,
             DS2_BUTTON_DOWN | DS2_BUTTON_LEFT | DS2_BUTTON_SQUARE |
                 DS2_BUTTON_TRIANGLE);

    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_RIGHT,
             DS2_BUTTON_UP | DS2_BUTTON_RIGHT);

    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_FORWARD_LEFT,
             DS2_BUTTON_UP | DS2_BUTTON_LEFT);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_RIGHT,
             DS2_BUTTON_DOWN | DS2_BUTTON_RIGHT);
    RUN_TEST(should_read_communication,
             COMM_MOVE_DIAG_BACKWARD_LEFT,
             DS2_BUTTON_DOWN | DS2_BUTTON_LEFT);

    RUN_TEST(
        should_read_communication, COMM_ROTATE_FACE_FRONT_RIGHT, DS2_BUTTON_R1);
    RUN_TEST(
        should_read_communication, COMM_ROTATE_FACE_FRONT_LEFT, DS2_BUTTON_L1);
    RUN_TEST(
        should_read_communication, COMM_ROTATE_FACE_REAR_RIGHT, DS2_BUTTON_R2);
    RUN_TEST(
        should_read_communication, COMM_ROTATE_FACE_REAR_LEFT, DS2_BUTTON_L2);

    RUN_TEST(should_read_communication,
             COMM_HARD_STOP,
             DS2_BUTTON_R1 | DS2_BUTTON_R2);
    RUN_TEST(should_read_communication,
             COMM_HARD_STOP,
             DS2_BUTTON_R1 | DS2_BUTTON_L1);
    RUN_TEST(should_read_communication,
             COMM_HARD_STOP,
             DS2_BUTTON_R1 | DS2_BUTTON_L2);
    RUN_TEST(should_read_communication,
             COMM_HARD_STOP,
             DS2_BUTTON_R2 | DS2_BUTTON_L1);
    RUN_TEST(should_read_communication,
             COMM_HARD_STOP,
             DS2_BUTTON_R2 | DS2_BUTTON_L2);
    RUN_TEST(should_read_communication,
             COMM_HARD_STOP,
             DS2_BUTTON_L1 | DS2_BUTTON_L2)

    return UNITY_END();
}
