#include "l293.h"

void l293_init(const l293_channel_t *channel)
{
  hal_gpio_init(&channel->a1);
  hal_gpio_init(&channel->a2);
}

void l293_set_channel(const l293_function_t function,
                      const l293_channel_t *channel)
{
  switch (function)
  {
    case L293_TURN_RIGHT:
      hal_gpio_write(&channel->a1, HAL_GPIO_LOW);
      hal_gpio_write(&channel->a2, HAL_GPIO_HIGH);
      break;
    case L293_TURN_LEFT:
      hal_gpio_write(&channel->a1, HAL_GPIO_HIGH);
      hal_gpio_write(&channel->a2, HAL_GPIO_LOW);
      break;
    case L293_FAST_STOP:
    default:
      hal_gpio_write(&channel->a1, HAL_GPIO_LOW);
      hal_gpio_write(&channel->a2, HAL_GPIO_LOW);
      break;
  }
}
