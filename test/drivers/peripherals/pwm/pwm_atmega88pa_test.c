#include "pwm.h"
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
    TCCR0A = 0;
    TCCR0B = 0;
    OCR0A  = 0;
}

void
should_init_timer0_pwm_phase_correct(void)
{
    // when
    pwm_init();

    // then
    TEST_ASSERT_BIT_HIGH(WGM00, TCCR0A);
    TEST_ASSERT_BIT_LOW(WGM01, TCCR0A);
    TEST_ASSERT_BIT_LOW(WGM02, TCCR0B);
}

void
should_init_timer0_pwm_channel_a_duty_cycle(void)
{
    // when
    pwm_init();

    // then
    TEST_ASSERT_BIT_HIGH(OC0A_BIT, OC0A_DDR);
    TEST_ASSERT_EQUAL_HEX8(0xd9, OCR0A);
}

void
should_run_pwm_with_256_prescaller(void)
{
    // when
    pwm_run();

    // then
    TEST_ASSERT_BIT_LOW(COM0A0, TCCR0A);
    TEST_ASSERT_BIT_HIGH(COM0A1, TCCR0A);
    TEST_ASSERT_BITS_LOW((1 << CS01) | (1 << CS00), TCCR0B);
    TEST_ASSERT_BIT_HIGH(CS02, TCCR0B);
}

void
should_stop_pwm(void)
{
    // when
    pwm_stop();

    // then
    TEST_ASSERT_BITS_LOW((1 << COM0A0) | (1 << COM0A1), TCCR0A);
    TEST_ASSERT_BITS_LOW((1 << CS02) | (1 << CS01) | (1 << CS00), TCCR0B);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_init_timer0_pwm_phase_correct);
    RUN_TEST(should_init_timer0_pwm_channel_a_duty_cycle);
    RUN_TEST(should_run_pwm_with_256_prescaller);
    RUN_TEST(should_stop_pwm);
    return UNITY_END();
}