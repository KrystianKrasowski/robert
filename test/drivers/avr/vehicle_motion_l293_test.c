#include "unity.h"
#include "unity_config.h"
#include "vehicle_motion_port.h"
#include <avr/io.h>

uint8_t DDRD   = 0;
uint8_t DDRC   = 0;
uint8_t PORTC  = 0;
uint8_t PORTD  = 0;
uint8_t TCCR0A = 0;
uint8_t TCCR0B = 0;
uint8_t OCR0A  = 0;

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
    vehicle_motion_init();

    // then
    TEST_ASSERT_BIT_HIGH(DDC2, DDRC);
    TEST_ASSERT_BIT_HIGH(DDC3, DDRC);
    TEST_ASSERT_BIT_HIGH(DDC4, DDRC);
    TEST_ASSERT_BIT_HIGH(DDC5, DDRC);
    // TODO: Uncomment it arter getting rid of avrhal
    // TEST_ASSERT_BIT_HIGH(DDD0, DDRD);
    // TEST_ASSERT_BIT_HIGH(DDD1, DDRD);
    // TEST_ASSERT_BIT_HIGH(DDD2, DDRD);
    // TEST_ASSERT_BIT_HIGH(DDD3, DDRD);
}

void
should_init_timer0_pwm_phase_correct(void)
{
    // when
    vehicle_motion_init();

    // then
    TEST_ASSERT_BIT_HIGH(WGM00, TCCR0A);
    TEST_ASSERT_BIT_LOW(WGM01, TCCR0A);
    TEST_ASSERT_BIT_LOW(WGM02, TCCR0B);
}

void
should_init_timer0_pwm_channel_a_duty_cycle(void)
{
    // when
    vehicle_motion_init();

    // then
    TEST_ASSERT_BIT_HIGH(OC0A_BIT, OC0A_DDR);
    TEST_ASSERT_EQUAL_HEX8(0xbf, OCR0A);
}

void
should_set_left_front_motor_gpio(vehicle_motion_t motion,
                                 uint8_t          expected_portc)
{
    // given
    vehicle_motion_init();
    vehicle_t vehicle = {.motor_left_front = motion};

    // when
    vehicle_motion_apply(&vehicle);

    // then
    TEST_ASSERT_BITS_HIGH(expected_portc, PORTC);
}

void
should_set_right_front_motor_gpio(vehicle_motion_t motion,
                                  uint8_t          expected_portd)
{
    // given
    vehicle_motion_init();
    vehicle_t vehicle = {.motor_right_front = motion};

    // when
    vehicle_motion_apply(&vehicle);

    // then
    // if ((mask & expected) != (mask & actual))
    TEST_ASSERT_BITS_HIGH(expected_portd, PORTD);
}

void
should_set_left_rear_motor_gpio(vehicle_motion_t motion, uint8_t expected_portc)
{
    // given
    vehicle_motion_init();
    vehicle_t vehicle = {.motor_left_rear = motion};

    // when
    vehicle_motion_apply(&vehicle);

    // then
    TEST_ASSERT_BITS_HIGH(expected_portc, PORTC);
}

void
should_set_right_rear_motor_gpio(vehicle_motion_t motion,
                                 uint8_t          expected_portd)
{
    // given
    vehicle_motion_init();
    vehicle_t vehicle = {.motor_right_rear = motion};

    // when
    vehicle_motion_apply(&vehicle);

    // then
    // if ((mask & expected) != (mask & actual))
    TEST_ASSERT_BITS_HIGH(expected_portd, PORTD);
}

void
should_run_pwm_with_256_prescaller(void)
{
    // given
    vehicle_motion_init();
    vehicle_t vehicle = {.current_command   = COMMAND_MOVE_FACE_FORWARD,
                         .motor_left_front  = MOTION_FORWARD,
                         .motor_right_front = MOTION_FORWARD,
                         .motor_left_rear   = MOTION_FORWARD,
                         .motor_right_rear  = MOTION_FORWARD};

    // when
    vehicle_motion_apply(&vehicle);

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
    vehicle_motion_init();
    vehicle_t vehicle = {.current_command   = COMMAND_SOFT_STOP,
                         .motor_left_front  = MOTION_NONE,
                         .motor_right_front = MOTION_NONE,
                         .motor_left_rear   = MOTION_NONE,
                         .motor_right_rear  = MOTION_NONE};

    // when
    vehicle_motion_apply(&vehicle);

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
    vehicle_motion_init();
    vehicle_t vehicle = {.current_command   = COMMAND_HARD_STOP,
                         .motor_left_front  = MOTION_NONE,
                         .motor_right_front = MOTION_NONE,
                         .motor_left_rear   = MOTION_NONE,
                         .motor_right_rear  = MOTION_NONE};

    // when
    vehicle_motion_apply(&vehicle);

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