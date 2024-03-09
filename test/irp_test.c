#include "irp.h"
#include "unity_config.h"
#include <unity/unity.h>

// t1nrm stubs
#include <avrhal/t1nrm.h>

#define PRESC_UNDEFINED 99
static hal_timer_prescaller_t _presc = PRESC_UNDEFINED;
static uint16_t _timer_value = 0xffff;
void hal_t1nrm_run(hal_timer_prescaller_t presc) { _presc = presc; }
void hal_t1nrm_set(uint16_t value) { _timer_value = value; }
void hal_t1nrm_stop(void) { _presc = PRESC_UNDEFINED; }

// t1int stubs
#include <avrhal/t1int.h>

static hal_t1int_cfg_t _timer1_interrupts;

void hal_t1int_configure(const hal_t1int_cfg_t *cfg)
{
  _timer1_interrupts = *cfg;
}

// helper functions
static void _valid_command(uint16_t v1,
                           uint16_t v2,
                           uint16_t v3,
                           uint16_t v4,
                           uint16_t v5,
                           uint16_t v6,
                           uint16_t v7,
                           uint16_t v8);
static uint16_t _negate(uint16_t value);

// tests
void setUp() { irp_release(); }

void tearDown() {}

void should_init_irp()
{
  // when
  irp_init();

  // then
  TEST_ASSERT_EQUAL(HAL_TIMER_PRESCALLER_8, _presc);
  TEST_ASSERT_EQUAL(1, _timer1_interrupts.timer_overflow);
  TEST_ASSERT_EQUAL(1, _timer1_interrupts.input_capture);
}

void should_return_nready_on_incomplete_command(void)
{
  // given
  for (int i = 0; i < 34; i++)
  {
    hal_t1int_on_input_capture(i);
  }

  // when
  irp_command_t command = irp_read();

  // then
  TEST_ASSERT_EQUAL(IRP_CMD_NREADY, command);
}

void should_return_cmd(uint16_t v1,
                       uint16_t v2,
                       uint16_t v3,
                       uint16_t v4,
                       uint16_t v5,
                       uint16_t v6,
                       uint16_t v7,
                       uint16_t v8,
                       uint8_t expected)
{
  // given
  _valid_command(v1, v2, v3, v4, v5, v6, v7, v8);

  // when
  irp_command_t command = irp_read();

  // then
  TEST_ASSERT_EQUAL_HEX8(expected, command);
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(should_init_irp, HAL_TIMER_PRESCALLER_1);
  RUN_TEST(should_return_nready_on_incomplete_command);
  RUN_TEST(should_return_cmd, 2500, 1400, 2500, 1400, 1400, 1400, 2500, 1400, 0xa2);
  RUN_TEST(should_return_cmd, 2500, 2500, 2500, 1400, 1400, 1400, 2500, 1400, 0xe2);
  RUN_TEST(should_return_cmd, 1400, 1400, 2500, 1400, 1400, 1400, 2500, 1400, 0x22);
  RUN_TEST(should_return_cmd, 1400, 1400, 1400, 1400, 1400, 1400, 2500, 1400, 0x02);
  RUN_TEST(should_return_cmd, 2500, 2500, 1400, 1400, 1400, 1400, 2500, 1400, 0xc2);
  RUN_TEST(should_return_cmd, 2500, 2500, 2500, 1400, 1400, 1400, 1400, 1400, 0xe0);
  RUN_TEST(should_return_cmd, 2500, 1400, 2500, 1400, 2500, 1400, 1400, 1400, 0xa8);
  RUN_TEST(should_return_cmd, 2500, 1400, 1400, 2500, 1400, 1400, 1400, 1400, 0x90);
  RUN_TEST(should_return_cmd, 1400, 2500, 2500, 1400, 2500, 1400, 1400, 1400, 0x68);
  RUN_TEST(should_return_cmd, 2500, 1400, 1400, 2500, 2500, 1400, 1400, 1400, 0x98);
  RUN_TEST(should_return_cmd, 2500, 1400, 2500, 2500, 1400, 1400, 1400, 1400, 0xb0);
  RUN_TEST(should_return_cmd, 1400, 1400, 2500, 2500, 1400, 1400, 1400, 1400, 0x30);
  RUN_TEST(should_return_cmd, 1400, 1400, 1400, 2500, 2500, 1400, 1400, 1400, 0x18);
  RUN_TEST(should_return_cmd, 1400, 2500, 2500, 2500, 2500, 1400, 2500, 1400, 0x7a);
  RUN_TEST(should_return_cmd, 1400, 1400, 1400, 2500, 1400, 1400, 1400, 1400, 0x10);
  RUN_TEST(should_return_cmd, 1400, 1400, 2500, 2500, 2500, 1400, 1400, 1400, 0x38);
  RUN_TEST(should_return_cmd, 1400, 2500, 1400, 2500, 2500, 1400, 2500, 1400, 0x5a);
  RUN_TEST(should_return_cmd, 1400, 2500, 1400, 1400, 1400, 1400, 2500, 1400, 0x42);
  RUN_TEST(should_return_cmd, 1400, 2500, 1400, 1400, 2500, 1400, 2500, 1400, 0x4a);
  RUN_TEST(should_return_cmd, 1400, 2500, 1400, 2500, 1400, 1400, 2500, 1400, 0x52);
  return UNITY_END();
}

static void _valid_command(uint16_t v1,
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
  hal_t1int_on_input_capture(IR_WIDTH_LOGIC_1);
  hal_t1int_on_input_capture(IR_WIDTH_LOGIC_1);
  hal_t1int_on_input_capture(IR_WIDTH_LOGIC_1);
  hal_t1int_on_input_capture(IR_WIDTH_LOGIC_1);
  hal_t1int_on_input_capture(IR_WIDTH_LOGIC_1);
  hal_t1int_on_input_capture(IR_WIDTH_LOGIC_1);
  hal_t1int_on_input_capture(IR_WIDTH_LOGIC_1);
  hal_t1int_on_input_capture(IR_WIDTH_LOGIC_1);
  // address negated
  hal_t1int_on_input_capture(IR_WIDTH_LOGIC_0);
  hal_t1int_on_input_capture(IR_WIDTH_LOGIC_0);
  hal_t1int_on_input_capture(IR_WIDTH_LOGIC_0);
  hal_t1int_on_input_capture(IR_WIDTH_LOGIC_0);
  hal_t1int_on_input_capture(IR_WIDTH_LOGIC_0);
  hal_t1int_on_input_capture(IR_WIDTH_LOGIC_0);
  hal_t1int_on_input_capture(IR_WIDTH_LOGIC_0);
  hal_t1int_on_input_capture(IR_WIDTH_LOGIC_0);
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
  hal_t1int_on_input_capture(_negate(v1));
  hal_t1int_on_input_capture(_negate(v2));
  hal_t1int_on_input_capture(_negate(v3));
  hal_t1int_on_input_capture(_negate(v4));
  hal_t1int_on_input_capture(_negate(v5));
  hal_t1int_on_input_capture(_negate(v6));
  hal_t1int_on_input_capture(_negate(v7));
  hal_t1int_on_input_capture(_negate(v8));
}

static uint16_t _negate(uint16_t value)
{
  if (value == IR_WIDTH_LOGIC_1)
  {
    return IR_WIDTH_LOGIC_0;
  }
  else
  {
    return IR_WIDTH_LOGIC_1;
  }
}
