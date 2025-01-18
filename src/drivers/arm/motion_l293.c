#include "drivers/motion.h"
#include "stm32f3xx.h"

// led is PB3
#define LED_PIN GPIO_ODR_3

static void
led_init(void);

void
motion_init(void)
{
    led_init();
}

void
motion_apply(motion_t *self, bool is_soft_stop)
{
    // TODO: Not implemented
}

static void
led_init(void)
{
    // enable clock access to GPIOB
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // set PB3 to alternate function
    GPIOB->MODER &= ~GPIO_MODER_MODER3_0;
    GPIOB->MODER |= GPIO_MODER_MODER3_1;

    // set PB3 alternate function to TIM2_CH2 / AF1
    GPIOB->AFR[0] |= (1U << 12);
    GPIOB->AFR[0] &= ~(1U << 13);
    GPIOB->AFR[0] &= ~(1U << 14);
    GPIOB->AFR[0] &= ~(1U << 15);

    // enable clock access to TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // set prestaler value
    TIM2->PSC = 800 - 1;

    // set auto-reload value
    TIM2->ARR = 2500 - 1;

    // set output compare toggle mode
    TIM2->CCMR1 |= TIM_CCMR1_OC2M_0 | TIM_CCMR1_OC2M_1;

    // enable channel 1 in compare mode
    TIM2->CCER |= TIM_CCER_CC2E;

    // clear counter
    TIM2->CNT = 0;

    // enable timer
    TIM2->CR1 |= TIM_CR1_CEN;
}