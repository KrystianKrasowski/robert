#include "gpio.h"
#include "stm32f3xx.h"

static void
gpio_init_l293_left_front_a1(void);

static void
gpio_init_l293_left_front_a2(void);



void
gpio_init_output(gpio_pin_t const pin)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    gpio_init_l293_left_front_a1();
    gpio_init_l293_left_front_a2();
}

void
gpio_set_output(gpio_pin_t const pin, gpio_state_t const state)
{
    GPIOA->ODR |= (1U << 0);
}

static void
gpio_init_l293_left_front_a1(void)
{
    // set PA0 as output
    GPIOA->MODER |= GPIO_MODER_MODER0_0;
    GPIOA->MODER &= ~GPIO_MODER_MODER0_1;
}

static void
gpio_init_l293_left_front_a2(void)
{
    // set PA1 as output
    GPIOA->MODER |= GPIO_MODER_MODER1_0;
    GPIOA->MODER &= ~GPIO_MODER_MODER1_1;
}