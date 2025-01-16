#include "drivers/motion.h"
#include "unity.h"
#include "unity_config.h"
#include <avr/io.h>

void
setUp(void)
{
}

void
tearDown(void)
{
    DDRD   = 0;
    DDRC   = 0;
    PORTC  = 0;
    PORTD  = 0;
    TCCR0A = 0;
    TCCR0B = 0;
    OCR0A  = 0;
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
should_set_left_front_motor_gpio(motion_direction_t direction,
                                 uint8_t            expected_portc)
{
    // when
    motion_t motion = {.left_front = direction};
    motion_apply(&motion, false);

    // then
    TEST_ASSERT_BITS_HIGH(expected_portc, PORTC);
}

void
should_set_right_front_motor_gpio(motion_direction_t direction,
                                  uint8_t            expected_portd)
{
    // when
    motion_t motion = {.right_front = direction};
    motion_apply(&motion, false);

    // then
    TEST_ASSERT_BITS_HIGH(expected_portd, PORTD);
}

void
should_set_left_rear_motor_gpio(motion_direction_t direction,
                                uint8_t            expected_portc)
{
    // when
    motion_t motion = {.left_rear = direction};
    motion_apply(&motion, false);

    // then
    TEST_ASSERT_BITS_HIGH(expected_portc, PORTC);
}

void
should_set_right_rear_motor_gpio(motion_direction_t direction,
                                 uint8_t            expected_portd)
{
    // when
    motion_t motion = {.right_rear = direction};
    motion_apply(&motion, false);

    // then
    TEST_ASSERT_BITS_HIGH(expected_portd, PORTD);
}

void
should_run_pwm_with_256_prescaller(void)
{
    // given
    motion_t motion = {.left_front  = MOTION_FORWARD,
                       .right_front = MOTION_FORWARD,
                       .left_rear   = MOTION_FORWARD,
                       .right_rear  = MOTION_FORWARD};

    // when
    motion_apply(&motion, false);

    // then
    TEST_ASSERT_BIT_LOW(COM0A0, TCCR0A);
    TEST_ASSERT_BIT_HIGH(COM0A1, TCCR0A);
    TEST_ASSERT_BITS_LOW((1 << CS01) | (1 << CS00), TCCR0B);
    TEST_ASSERT_BIT_HIGH(CS02, TCCR0B);
}

void
should_stop_running(void)
{
    // given
    motion_t motion = {.left_front  = MOTION_NONE,
                       .right_front = MOTION_NONE,
                       .left_rear   = MOTION_NONE,
                       .right_rear  = MOTION_NONE};

    // when
    motion_apply(&motion, true);

    // then
    TEST_ASSERT_EQUAL(0, PORTC);
    TEST_ASSERT_EQUAL(0, PORTD);
    TEST_ASSERT_BITS_LOW((1 << COM0A0) | (1 << COM0A1), TCCR0A);
    TEST_ASSERT_BITS_LOW((1 << CS02) | (1 << CS01) | (1 << CS00), TCCR0B);
}

void
should_stop_immediately(void)
{
    // given
    motion_t motion = {.left_front  = MOTION_NONE,
                       .right_front = MOTION_NONE,
                       .left_rear   = MOTION_NONE,
                       .right_rear  = MOTION_NONE};

    // when
    motion_apply(&motion, false);

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
    RUN_PARAM_TEST(should_set_left_front_motor_gpio, MOTION_FORWARD, 0x04);
    RUN_PARAM_TEST(should_set_left_front_motor_gpio, MOTION_BACKWARD, 0x08);
    RUN_PARAM_TEST(should_set_left_front_motor_gpio, MOTION_NONE, 0);
    RUN_PARAM_TEST(should_set_right_front_motor_gpio, MOTION_FORWARD, 0x02);
    RUN_PARAM_TEST(should_set_right_front_motor_gpio, MOTION_BACKWARD, 0x01);
    RUN_PARAM_TEST(should_set_right_front_motor_gpio, MOTION_NONE, 0);
    RUN_PARAM_TEST(should_set_left_rear_motor_gpio, MOTION_FORWARD, 0x10);
    RUN_PARAM_TEST(should_set_left_rear_motor_gpio, MOTION_BACKWARD, 0x20);
    RUN_PARAM_TEST(should_set_left_rear_motor_gpio, MOTION_NONE, 0);
    RUN_PARAM_TEST(should_set_right_rear_motor_gpio, MOTION_FORWARD, 0x08);
    RUN_PARAM_TEST(should_set_right_rear_motor_gpio, MOTION_BACKWARD, 0x04);
    RUN_PARAM_TEST(should_set_right_rear_motor_gpio, MOTION_NONE, 0);
    RUN_TEST(should_run_pwm_with_256_prescaller);
    RUN_TEST(should_stop_running);
    RUN_TEST(should_stop_immediately);
    return UNITY_END();
}