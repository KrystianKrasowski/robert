#include "drivers/command.h"
#include "drivers/command_mock.h"
#include "drivers/motion.h"
#include "drivers/motion_mock.h"
#include "unity.h"
#include "unity_config.h"
#include "vehicle.h"

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_initialize_drivers(void)
{
    // when
    vehicle_init();

    // then
    TEST_ASSERT_TRUE(command_mock_is_initilized());
    TEST_ASSERT_TRUE(motion_mock_is_initialized());
}

void
should_run(command_t          command,
           motion_direction_t expected_left_front,
           motion_direction_t expected_right_front,
           motion_direction_t expected_left_rear,
           motion_direction_t expected_right_rear)
{
    // given
    command_mock_given_command(command);

    // when
    vehicle_run();

    // then
    TEST_ASSERT_TRUE(motion_mock_verify_left_front(expected_left_front));
    TEST_ASSERT_TRUE(motion_mock_verify_right_front(expected_right_front));
    TEST_ASSERT_TRUE(motion_mock_verify_left_rear(expected_left_rear));
    TEST_ASSERT_TRUE(motion_mock_verify_right_rear(expected_right_rear));
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_initialize_drivers);

    RUN_PARAM_TEST(should_run,
                   COMMAND_MOVE_FACE_FORWARD,
                   MOTION_FORWARD,
                   MOTION_FORWARD,
                   MOTION_FORWARD,
                   MOTION_FORWARD);

    RUN_PARAM_TEST(should_run,
                   COMMAND_MOVE_FACE_BACKWARD,
                   MOTION_BACKWARD,
                   MOTION_BACKWARD,
                   MOTION_BACKWARD,
                   MOTION_BACKWARD);

    RUN_PARAM_TEST(should_run,
                   COMMAND_MOVE_SIDE_RIGHT,
                   MOTION_FORWARD,
                   MOTION_BACKWARD,
                   MOTION_BACKWARD,
                   MOTION_FORWARD);

    RUN_PARAM_TEST(should_run,
                   COMMAND_MOVE_SIDE_LEFT,
                   MOTION_BACKWARD,
                   MOTION_FORWARD,
                   MOTION_FORWARD,
                   MOTION_BACKWARD);

    RUN_PARAM_TEST(should_run,
                   COMMAND_MOVE_DIAG_FORWARD_RIGHT,
                   MOTION_FORWARD,
                   MOTION_NONE,
                   MOTION_NONE,
                   MOTION_FORWARD);

    RUN_PARAM_TEST(should_run,
                   COMMAND_MOVE_DIAG_FORWARD_LEFT,
                   MOTION_NONE,
                   MOTION_FORWARD,
                   MOTION_FORWARD,
                   MOTION_NONE);

    RUN_PARAM_TEST(should_run,
                   COMMAND_MOVE_DIAG_BACKWARD_RIGHT,
                   MOTION_NONE,
                   MOTION_BACKWARD,
                   MOTION_BACKWARD,
                   MOTION_NONE);

    RUN_PARAM_TEST(should_run,
                   COMMAND_MOVE_DIAG_BACKWARD_LEFT,
                   MOTION_BACKWARD,
                   MOTION_NONE,
                   MOTION_NONE,
                   MOTION_BACKWARD);

    RUN_PARAM_TEST(should_run,
                   COMMAND_ROTATE_SIDE_RIGHT_FORWARD,
                   MOTION_NONE,
                   MOTION_FORWARD,
                   MOTION_NONE,
                   MOTION_FORWARD);

    RUN_PARAM_TEST(should_run,
                   COMMAND_ROTATE_SIDE_RIGHT_BACKWARD,
                   MOTION_NONE,
                   MOTION_BACKWARD,
                   MOTION_NONE,
                   MOTION_BACKWARD);

    RUN_PARAM_TEST(should_run,
                   COMMAND_ROTATE_SIDE_LEFT_FORWARD,
                   MOTION_FORWARD,
                   MOTION_NONE,
                   MOTION_FORWARD,
                   MOTION_NONE);

    RUN_PARAM_TEST(should_run,
                   COMMAND_ROTATE_SIDE_LEFT_BACKWARD,
                   MOTION_BACKWARD,
                   MOTION_NONE,
                   MOTION_BACKWARD,
                   MOTION_NONE);

    RUN_PARAM_TEST(should_run,
                   COMMAND_ROTATE_RIGHT,
                   MOTION_FORWARD,
                   MOTION_BACKWARD,
                   MOTION_FORWARD,
                   MOTION_BACKWARD);

    RUN_PARAM_TEST(should_run,
                   COMMAND_ROTATE_LEFT,
                   MOTION_BACKWARD,
                   MOTION_FORWARD,
                   MOTION_BACKWARD,
                   MOTION_FORWARD);

    RUN_PARAM_TEST(should_run,
                   COMMAND_ROTATE_FACE_FRONT_RIGHT,
                   MOTION_FORWARD,
                   MOTION_BACKWARD,
                   MOTION_NONE,
                   MOTION_NONE);

    RUN_PARAM_TEST(should_run,
                   COMMAND_ROTATE_FACE_FRONT_LEFT,
                   MOTION_BACKWARD,
                   MOTION_FORWARD,
                   MOTION_NONE,
                   MOTION_NONE);

    RUN_PARAM_TEST(should_run,
                   COMMAND_ROTATE_FACE_REAR_RIGHT,
                   MOTION_NONE,
                   MOTION_NONE,
                   MOTION_BACKWARD,
                   MOTION_FORWARD);

    RUN_PARAM_TEST(should_run,
                   COMMAND_ROTATE_FACE_REAR_LEFT,
                   MOTION_NONE,
                   MOTION_NONE,
                   MOTION_FORWARD,
                   MOTION_BACKWARD);

    RUN_PARAM_TEST(should_run,
                   COMMAND_SOFT_STOP,
                   MOTION_NONE,
                   MOTION_NONE,
                   MOTION_NONE,
                   MOTION_NONE);

    RUN_PARAM_TEST(should_run,
                   COMMAND_HARD_STOP,
                   MOTION_NONE,
                   MOTION_NONE,
                   MOTION_NONE,
                   MOTION_NONE);

    return UNITY_END();
}