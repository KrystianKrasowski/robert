#include "infrared_pilot.h"
#include "unity_config.h"
#include <avrhal/t1int.h>
#include <avrhal/t1nrm.h>
#include <unity/unity.h>

// t1nrm stubs
#define PRESCALLER_UNDEFINED 99
static hal_timer_prescaller_t prescaller  = PRESCALLER_UNDEFINED;
static uint16_t               timer_value = 0xffff;

void
hal_t1nrm_run(hal_timer_prescaller_t presc)
{
    prescaller = presc;
}

void
hal_t1nrm_set(uint16_t value)
{
    timer_value = value;
}

void
hal_t1nrm_stop(void)
{
    prescaller = PRESCALLER_UNDEFINED;
}

// t1int stubs
static hal_t1int_cfg_t _timer1_interrupts;

void
hal_t1int_configure(const hal_t1int_cfg_t *cfg)
{
    _timer1_interrupts = *cfg;
}

// helper functions
static void
valid_command(uint16_t v1,
              uint16_t v2,
              uint16_t v3,
              uint16_t v4,
              uint16_t v5,
              uint16_t v6,
              uint16_t v7,
              uint16_t v8);

static uint16_t
negate(uint16_t value);

// tests
void
setUp()
{
    infrared_pilot_release();
}

void
tearDown()
{
}

void
should_init_irp()
{
    // when
    infrared_pilot_init();

    // then
    TEST_ASSERT_EQUAL(HAL_TIMER_PRESCALLER_8, prescaller);
    TEST_ASSERT_EQUAL(1, _timer1_interrupts.timer_overflow);
    TEST_ASSERT_EQUAL(1, _timer1_interrupts.input_capture);
}

void
should_return_nready_on_incomplete_command(void)
{
    // given
    for (int i = 0; i < 34; i++)
    {
        hal_t1int_on_input_capture(i);
    }

    // when
    infrared_pilot_command_t command = infrared_pilot_read();

    // then
    TEST_ASSERT_EQUAL(IRP_CMD_NREADY, command);
}

void
should_return_cmd(uint16_t v1,
                  uint16_t v2,
                  uint16_t v3,
                  uint16_t v4,
                  uint16_t v5,
                  uint16_t v6,
                  uint16_t v7,
                  uint16_t v8,
                  uint8_t  expected)
{
    // given
    valid_command(v1, v2, v3, v4, v5, v6, v7, v8);

    // when
    infrared_pilot_command_t command = infrared_pilot_read();

    // then
    TEST_ASSERT_EQUAL_HEX8(expected, command);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_init_irp, HAL_TIMER_PRESCALLER_1);
    RUN_TEST(should_return_nready_on_incomplete_command);
    RUN_TEST(should_return_cmd,
             2500,
             1400,
             2500,
             1400,
             1400,
             1400,
             2500,
             1400,
             0xa2);
    RUN_TEST(should_return_cmd,
             2500,
             2500,
             2500,
             1400,
             1400,
             1400,
             2500,
             1400,
             0xe2);
    RUN_TEST(should_return_cmd,
             1400,
             1400,
             2500,
             1400,
             1400,
             1400,
             2500,
             1400,
             0x22);
    RUN_TEST(should_return_cmd,
             1400,
             1400,
             1400,
             1400,
             1400,
             1400,
             2500,
             1400,
             0x02);
    RUN_TEST(should_return_cmd,
             2500,
             2500,
             1400,
             1400,
             1400,
             1400,
             2500,
             1400,
             0xc2);
    RUN_TEST(should_return_cmd,
             2500,
             2500,
             2500,
             1400,
             1400,
             1400,
             1400,
             1400,
             0xe0);
    RUN_TEST(should_return_cmd,
             2500,
             1400,
             2500,
             1400,
             2500,
             1400,
             1400,
             1400,
             0xa8);
    RUN_TEST(should_return_cmd,
             2500,
             1400,
             1400,
             2500,
             1400,
             1400,
             1400,
             1400,
             0x90);
    RUN_TEST(should_return_cmd,
             1400,
             2500,
             2500,
             1400,
             2500,
             1400,
             1400,
             1400,
             0x68);
    RUN_TEST(should_return_cmd,
             2500,
             1400,
             1400,
             2500,
             2500,
             1400,
             1400,
             1400,
             0x98);
    RUN_TEST(should_return_cmd,
             2500,
             1400,
             2500,
             2500,
             1400,
             1400,
             1400,
             1400,
             0xb0);
    RUN_TEST(should_return_cmd,
             1400,
             1400,
             2500,
             2500,
             1400,
             1400,
             1400,
             1400,
             0x30);
    RUN_TEST(should_return_cmd,
             1400,
             1400,
             1400,
             2500,
             2500,
             1400,
             1400,
             1400,
             0x18);
    RUN_TEST(should_return_cmd,
             1400,
             2500,
             2500,
             2500,
             2500,
             1400,
             2500,
             1400,
             0x7a);
    RUN_TEST(should_return_cmd,
             1400,
             1400,
             1400,
             2500,
             1400,
             1400,
             1400,
             1400,
             0x10);
    RUN_TEST(should_return_cmd,
             1400,
             1400,
             2500,
             2500,
             2500,
             1400,
             1400,
             1400,
             0x38);
    RUN_TEST(should_return_cmd,
             1400,
             2500,
             1400,
             2500,
             2500,
             1400,
             2500,
             1400,
             0x5a);
    RUN_TEST(should_return_cmd,
             1400,
             2500,
             1400,
             1400,
             1400,
             1400,
             2500,
             1400,
             0x42);
    RUN_TEST(should_return_cmd,
             1400,
             2500,
             1400,
             1400,
             2500,
             1400,
             2500,
             1400,
             0x4a);
    RUN_TEST(should_return_cmd,
             1400,
             2500,
             1400,
             2500,
             1400,
             1400,
             2500,
             1400,
             0x52);
    return UNITY_END();
}

static void
valid_command(uint16_t v1,
              uint16_t v2,
              uint16_t v3,
              uint16_t v4,
              uint16_t v5,
              uint16_t v6,
              uint16_t v7,
              uint16_t v8)
{
    // first is ommited
    hal_t1int_on_input_capture(99);
    // transmission start
    hal_t1int_on_input_capture(14000);
    // address
    hal_t1int_on_input_capture(INFRARED_PILOT_WIDTH_LOGIC_1);
    hal_t1int_on_input_capture(INFRARED_PILOT_WIDTH_LOGIC_1);
    hal_t1int_on_input_capture(INFRARED_PILOT_WIDTH_LOGIC_1);
    hal_t1int_on_input_capture(INFRARED_PILOT_WIDTH_LOGIC_1);
    hal_t1int_on_input_capture(INFRARED_PILOT_WIDTH_LOGIC_1);
    hal_t1int_on_input_capture(INFRARED_PILOT_WIDTH_LOGIC_1);
    hal_t1int_on_input_capture(INFRARED_PILOT_WIDTH_LOGIC_1);
    hal_t1int_on_input_capture(INFRARED_PILOT_WIDTH_LOGIC_1);
    // address negated
    hal_t1int_on_input_capture(INFRARED_PILOT_WIDTH_LOGIC_0);
    hal_t1int_on_input_capture(INFRARED_PILOT_WIDTH_LOGIC_0);
    hal_t1int_on_input_capture(INFRARED_PILOT_WIDTH_LOGIC_0);
    hal_t1int_on_input_capture(INFRARED_PILOT_WIDTH_LOGIC_0);
    hal_t1int_on_input_capture(INFRARED_PILOT_WIDTH_LOGIC_0);
    hal_t1int_on_input_capture(INFRARED_PILOT_WIDTH_LOGIC_0);
    hal_t1int_on_input_capture(INFRARED_PILOT_WIDTH_LOGIC_0);
    hal_t1int_on_input_capture(INFRARED_PILOT_WIDTH_LOGIC_0);
    // command
    hal_t1int_on_input_capture(v1);
    hal_t1int_on_input_capture(v2);
    hal_t1int_on_input_capture(v3);
    hal_t1int_on_input_capture(v4);
    hal_t1int_on_input_capture(v5);
    hal_t1int_on_input_capture(v6);
    hal_t1int_on_input_capture(v7);
    hal_t1int_on_input_capture(v8);
    // command negated
    hal_t1int_on_input_capture(negate(v1));
    hal_t1int_on_input_capture(negate(v2));
    hal_t1int_on_input_capture(negate(v3));
    hal_t1int_on_input_capture(negate(v4));
    hal_t1int_on_input_capture(negate(v5));
    hal_t1int_on_input_capture(negate(v6));
    hal_t1int_on_input_capture(negate(v7));
    hal_t1int_on_input_capture(negate(v8));
}

static uint16_t
negate(uint16_t value)
{
    if (value == INFRARED_PILOT_WIDTH_LOGIC_1)
    {
        return INFRARED_PILOT_WIDTH_LOGIC_0;
    }
    else
    {
        return INFRARED_PILOT_WIDTH_LOGIC_1;
    }
}
