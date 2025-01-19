#include "timer.h"
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
}

void
should_init_timer1_in_ctc_mode(void)
{
    // when
    timer_init();

    // then
    TEST_ASSERT_FALSE(TCCR1A);
    TEST_ASSERT_BIT_HIGH(WGM12, TCCR1B);
}

void
should_init_timer1_with_8_prescaller(void)
{
    // when
    timer_init();

    // then
    TEST_ASSERT_BIT_LOW(CS12, TCCR1B);
    TEST_ASSERT_BIT_LOW(CS10, TCCR1B);
    TEST_ASSERT_BIT_HIGH(CS11, TCCR1B);
}

void
should_init_timer1_channels_resolution()
{
    // when
    timer_init();

    // then
    TEST_ASSERT_EQUAL(16000, OCR1A);
    TEST_ASSERT_EQUAL(200, OCR1B);
}

void
should_init_output_compare_interrupt_on_timer1_both_channels(void)
{
    // when
    timer_init();

    // then
    TEST_ASSERT_BIT_HIGH(OCIE1A, TIMSK1);
    TEST_ASSERT_BIT_HIGH(OCIE1B, TIMSK1);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_init_timer1_in_ctc_mode);
    RUN_TEST(should_init_timer1_with_8_prescaller);
    RUN_TEST(should_init_timer1_channels_resolution);
    RUN_TEST(should_init_output_compare_interrupt_on_timer1_both_channels);
    return UNITY_END();
}