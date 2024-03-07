#ifndef _L293_H
#define _L293_H

#include <avrhal/gpio.h>
#include <stdint.h>

typedef struct
{
  hal_gpio_def_t a1;
  hal_gpio_def_t a2;
} l293_channel_t;

typedef enum
{
  L293_TURN_LEFT,
  L293_TURN_RIGHT,
  L293_FAST_STOP,
} l293_function_t;

void l293_init(const l293_channel_t *channel);
void l293_set_channel(const l293_function_t function,
                      const l293_channel_t *channel);

#endif
