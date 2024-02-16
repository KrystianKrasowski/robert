#ifndef _LIBAVRHAL_T1INT_MOCK
#define _LIBAVRHAL_T1INT_MOCK

#include <stdint.h>

typedef struct
{
  uint8_t timer_overflow : 1;
  uint8_t output_compare_a : 1;
  uint8_t output_compare_b : 1;
  uint8_t : 2;
  uint8_t input_capture : 1;
  uint8_t : 2;
} hal_t1int_cfg_t;

void hal_t1int_configure(const hal_t1int_cfg_t *cfg);
__attribute__((weak)) void hal_t1int_on_input_capture(const uint16_t value);
__attribute__((weak)) void hal_t1int_on_timer_overflow(void);

#endif