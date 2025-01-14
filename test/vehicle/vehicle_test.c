#include "unity.h"
#include "unity_config.h"
#include "vehicle.h"
#include "vehicle_command_mock.h"
#include "vehicle_motion_mock.h"

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_initialize_vehicle(void)
{
    // given
    vehicle_t vehicle = {};

    // when
    vehicle_init(&vehicle);

    // then
    TEST_ASSERT_EQUAL(COMMAND_SOFT_STOP, vehicle.current_command);
    TEST_ASSERT_EQUAL(MOTION_NONE, vehicle.motor_left_front);
    TEST_ASSERT_EQUAL(MOTION_NONE, vehicle.motor_right_front);
    TEST_ASSERT_EQUAL(MOTION_NONE, vehicle.motor_left_rear);
    TEST_ASSERT_EQUAL(MOTION_NONE, vehicle.motor_right_rear);
}

void
should_initialize_vehicle_ports(void)
{
    // given
    vehicle_t vehicle = {};

    // when
    vehicle_init(&vehicle);

    // then
    TEST_ASSERT_TRUE(vehicle_command_mock_is_initilized());
    TEST_ASSERT_TRUE(vehicle_motion_mock_is_initialized());
}

void
should_run(vehicle_command_t command,
           vehicle_motion_t  expected_left_front,
           vehicle_motion_t  expected_right_front,
           vehicle_motion_t  expected_left_rear,
           vehicle_motion_t  expected_right_rear)
{
    // given
    vehicle_t vehicle = {};
    vehicle_init(&vehicle);
    vehicle_command_mock_given_command(command);

    // when
    vehicle_run(&vehicle);

    // then
    TEST_ASSERT_EQUAL(expected_left_front, vehicle.motor_left_front);
    TEST_ASSERT_EQUAL(expected_right_front, vehicle.motor_right_front);
    TEST_ASSERT_EQUAL(expected_left_rear, vehicle.motor_left_rear);
    TEST_ASSERT_EQUAL(expected_right_rear, vehicle.motor_right_rear);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_initialize_vehicle);
    RUN_TEST(should_initialize_vehicle_ports);

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