#include "comm.h"
#include "ds2.h"
#include "unity_config.h"
#include <stdint.h>
#include <unity/unity.h>

typedef struct
{
  uint8_t initialized;
  uint16_t buttons;
} ds2_state_t;

ds2_state_t ds2_state = {};

void ds2_init(void) { ds2_state.initialized = 1; }

uint16_t ds2_read(void) { return ds2_state.buttons; }

void setUp()
{
  ds2_state.initialized = 0;
  ds2_state.buttons = DS2_NONE;
}

void tearDown() {}

void should_initialize_dualshock2(void)
{
  // when
  comm_init();

  // then
  TEST_ASSERT_TRUE(ds2_state.initialized);
}

void should_read_communication(comm_command_t expected, uint16_t buttons)
{
  // given
  ds2_state.buttons = buttons;

  // when
  comm_command_t actual = comm_read();

  // then
  TEST_ASSERT_EQUAL(expected, actual);
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(should_initialize_dualshock2);
  RUN_TEST(should_read_communication, COMM_ROTATE_SIDE_RIGHT_FORWARD, DS2_BUTTON_UP | DS2_BUTTON_SQUARE);
  RUN_TEST(should_read_communication, COMM_MOVE_FACE_FORWARD, DS2_BUTTON_UP);
  return UNITY_END();
}
