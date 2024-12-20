#include "motion.h"
#include "unity_config.h"
#include <avr/io.h>
#include <unity.h>

// TODO: remove this function and its usages after refactoring the driver
// It is necessary due to kept state on the avrhal library. Simple register
// reset is not enough
static void
motion_set_all_stopped(void);

void
setUp(void)
{

}

void
tearDown(void)
{
    motion_set_all_stopped();
}

void
should_init_gpio(void)
{
    // when
    motion_init();

    // then
    TEST_ASSERT_BIT_HIGH(DDC2, DDRC);
    TEST_ASSERT_BIT_HIGH(DDC3, DDRC);
    TEST_ASSERT_BIT_HIGH(DDC4, DDRC);
    TEST_ASSERT_BIT_HIGH(DDC5, DDRC);
    TEST_ASSERT_BIT_HIGH(DDD0, DDRD);
    TEST_ASSERT_BIT_HIGH(DDD1, DDRD);
    TEST_ASSERT_BIT_HIGH(DDD2, DDRD);
    TEST_ASSERT_BIT_HIGH(DDD3, DDRD);
}

void
should_init_timer0_pwm_phase_correct(void)
{
    // when
    motion_init();

    // then
    TEST_ASSERT_BIT_HIGH(WGM00, TCCR0A);
    TEST_ASSERT_BIT_LOW(WGM01, TCCR0A);
    TEST_ASSERT_BIT_LOW(WGM02, TCCR0B);
}

void
should_init_timer0_pwm_channel_a_duty_cycle(void)
{
    // when
    motion_init();

    // then
    TEST_ASSERT_BIT_HIGH(OC0A_BIT, OC0A_DDR);
    TEST_ASSERT_EQUAL_HEX8(0xbf, OCR0A);
}

void
should_init_timer0_pwm_channel_b_disconnected(void)
{
    // when
    motion_init();

    // then
    TEST_ASSERT_BIT_LOW(OC0B_BIT, OC0B_DDR);
}

void
should_run_pwm_with_256_prescaller(void)
{
    // when
    motion_run();

    // then
    TEST_ASSERT_BIT_LOW(COM0A0, TCCR0A);
    TEST_ASSERT_BIT_HIGH(COM0A1, TCCR0A);
    TEST_ASSERT_BITS_LOW((1 << CS01) | (1 << CS00), TCCR0B);
    TEST_ASSERT_BIT_HIGH(CS02, TCCR0B);
}

void
should_run(motion_motor_t     motor,
           motion_direction_t dir,
           uint8_t            portc,
           uint8_t            portd)
{
    // when
    motion_t motion = {motor, dir};
    motion_set(&motion);
    motion_run();

    // then
    TEST_ASSERT_EQUAL(portc, PORTC);
    TEST_ASSERT_EQUAL(portd, PORTD);
}

void
should_stop_running(motion_motor_t motor)
{
    // given
    motion_t initial_motion = {motor, MOTION_DIR_FWD};
    motion_set(&initial_motion);
    motion_run();

    // when
    motion_t motion = {motor, MOTION_DIR_STOP};
    motion_set(&motion);
    motion_stop_running();

    // then
    TEST_ASSERT_EQUAL(0, PORTC);
    TEST_ASSERT_EQUAL(0, PORTD);
    TEST_ASSERT_BITS_LOW((1 << COM0A0) | (1 << COM0A1), TCCR0A);
    TEST_ASSERT_BITS_LOW((1 << COM0B0) | (1 << COM0B1), TCCR0A);
    TEST_ASSERT_BITS_LOW((1 << CS02) | (1 << CS01) | (1 << CS00), TCCR0B);
}

void
should_stop_immediately(motion_motor_t motor)
{
    // given
    motion_t initial_motion = {motor, MOTION_DIR_FWD};
    motion_set(&initial_motion);
    motion_run();

    // when
    motion_t motion = {motor, MOTION_DIR_STOP};
    motion_set(&motion);
    motion_stop();

    // then
    TEST_ASSERT_EQUAL(0, PORTC);
    TEST_ASSERT_EQUAL(0, PORTD);
    TEST_ASSERT_BIT_LOW(COM0A0, TCCR0A);
    TEST_ASSERT_BIT_HIGH(COM0A1, TCCR0A);
    TEST_ASSERT_BITS_LOW((1 << CS01) | (1 << CS00), TCCR0B);
    TEST_ASSERT_BIT_HIGH(CS02, TCCR0B);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_init_gpio);
    RUN_TEST(should_init_timer0_pwm_phase_correct);
    RUN_TEST(should_init_timer0_pwm_channel_a_duty_cycle);
    RUN_TEST(should_init_timer0_pwm_channel_b_disconnected);
    RUN_TEST(should_run_pwm_with_256_prescaller);
    RUN_PARAM_TEST(
        should_run, MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_FWD, 0b00000100, 0);
    RUN_PARAM_TEST(
        should_run, MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_BCK, 0b00001000, 0);
    RUN_PARAM_TEST(
        should_run, MOTION_MOTOR_LEFT_REAR, MOTION_DIR_FWD, 0b00010000, 0);
    RUN_PARAM_TEST(
        should_run, MOTION_MOTOR_LEFT_REAR, MOTION_DIR_BCK, 0b00100000, 0);
    RUN_PARAM_TEST(
        should_run, MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_FWD, 0, 0b00000010);
    RUN_PARAM_TEST(
        should_run, MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_BCK, 0, 0b00000001);
    RUN_PARAM_TEST(
        should_run, MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_FWD, 0, 0b00001000);
    RUN_PARAM_TEST(
        should_run, MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_BCK, 0, 0b00000100);
    RUN_PARAM_TEST(should_stop_running, MOTION_MOTOR_LEFT_FRONT);
    RUN_PARAM_TEST(should_stop_running, MOTION_MOTOR_LEFT_REAR);
    RUN_PARAM_TEST(should_stop_running, MOTION_MOTOR_RIGHT_FRONT);
    RUN_PARAM_TEST(should_stop_running, MOTION_MOTOR_RIGHT_REAR);
    RUN_PARAM_TEST(should_stop_immediately, MOTION_MOTOR_LEFT_FRONT);
    RUN_PARAM_TEST(should_stop_immediately, MOTION_MOTOR_LEFT_REAR);
    RUN_PARAM_TEST(should_stop_immediately, MOTION_MOTOR_RIGHT_FRONT);
    RUN_PARAM_TEST(should_stop_immediately, MOTION_MOTOR_RIGHT_REAR);

    return UNITY_END();
}

static void
motion_set_all_stopped(void)
{
    motion_t left_front  = {MOTION_MOTOR_LEFT_FRONT, MOTION_DIR_STOP};
    motion_t left_rear   = {MOTION_MOTOR_LEFT_REAR, MOTION_DIR_STOP};
    motion_t right_front = {MOTION_MOTOR_RIGHT_FRONT, MOTION_DIR_STOP};
    motion_t right_rear  = {MOTION_MOTOR_RIGHT_REAR, MOTION_DIR_STOP};
    motion_set(&left_front);
    motion_set(&left_rear);
    motion_set(&right_front);
    motion_set(&right_rear);
    motion_stop_running();
}