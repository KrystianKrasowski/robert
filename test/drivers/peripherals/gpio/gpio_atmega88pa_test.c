#include "gpio.h"
#include "unity.h"
#include "unity_config.h"
#include <avr/io.h>

void
setUp()
{
}

void
tearDown()
{
    gpio_reset_modes();
    gpio_reset_states();
}

void
should_init_as_output(gpio_pin_t pin, uint8_t bit, uint8_t *DDRx)
{
    // when
    gpio_init_output(pin);
    gpio_apply_modes();

    // then
    TEST_ASSERT_BIT_HIGH(bit, *DDRx);
}

void
should_set_high(gpio_pin_t pin, uint8_t bit, uint8_t *PORTx)
{
    // when
    gpio_set_output(pin, GPIO_STATE_HIGH);
    gpio_apply_states();

    // then
    TEST_ASSERT_BIT_HIGH(bit, *PORTx);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_PARAM_TEST(should_init_as_output, GPIO_L293_LEFT_FRONT_A1, 3, &DDRC);
    RUN_PARAM_TEST(should_init_as_output, GPIO_L293_LEFT_FRONT_A2, 2, &DDRC);
    RUN_PARAM_TEST(should_init_as_output, GPIO_L293_RIGHT_FRONT_A1, 0, &DDRD);
    RUN_PARAM_TEST(should_init_as_output, GPIO_L293_RIGHT_FRONT_A2, 1, &DDRD);
    RUN_PARAM_TEST(should_init_as_output, GPIO_L293_LEFT_REAR_A1, 5, &DDRC);
    RUN_PARAM_TEST(should_init_as_output, GPIO_L293_LEFT_REAR_A2, 4, &DDRC);
    RUN_PARAM_TEST(should_init_as_output, GPIO_L293_RIGHT_REAR_A1, 2, &DDRD);
    RUN_PARAM_TEST(should_init_as_output, GPIO_L293_RIGHT_REAR_A2, 3, &DDRD);
    RUN_PARAM_TEST(should_init_as_output, GPIO_DUALSHOCK2_ATTENTION, 1, &DDRB);
    RUN_PARAM_TEST(should_set_high, GPIO_L293_LEFT_FRONT_A1, 3, &PORTC);
    RUN_PARAM_TEST(should_set_high, GPIO_L293_LEFT_FRONT_A2, 2, &PORTC);
    RUN_PARAM_TEST(should_set_high, GPIO_L293_RIGHT_FRONT_A1, 0, &PORTD);
    RUN_PARAM_TEST(should_set_high, GPIO_L293_RIGHT_FRONT_A2, 1, &PORTD);
    RUN_PARAM_TEST(should_set_high, GPIO_L293_LEFT_REAR_A1, 5, &PORTC);
    RUN_PARAM_TEST(should_set_high, GPIO_L293_LEFT_REAR_A2, 4, &PORTC);
    RUN_PARAM_TEST(should_set_high, GPIO_L293_RIGHT_REAR_A1, 2, &PORTD);
    RUN_PARAM_TEST(should_set_high, GPIO_L293_RIGHT_REAR_A2, 3, &PORTD);
    RUN_PARAM_TEST(should_set_high, GPIO_DUALSHOCK2_ATTENTION, 1, &PORTB);
    return UNITY_END();
}