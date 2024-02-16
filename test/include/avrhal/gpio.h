#ifndef _AVRHAL_GPIO_MOCK
#define _AVRHAL_GPIO_MOCK

typedef enum
{
  HAL_GPIO_INPUT,
  HAL_GPIO_INPUT_WITH_PULLUP,
  HAL_GPIO_OUTPUT
} hal_gpio_dir_t;

typedef enum
{
  HAL_GPIO_REGB,
  HAL_GPIO_REGC,
  HAL_GPIO_REGD
} hal_gpio_reg_t;

typedef struct
{
  hal_gpio_reg_t reg;
  hal_gpio_dir_t dir;
  uint8_t pin;
} hal_gpio_def_t;

#endif