#include "pwm.h"
#include "stm32f303x8.h"

void
pwm_init(void)
{
    // enable clock access to GPIOA if necessary
    if ((RCC->AHBENR & RCC_AHBENR_GPIOAEN) == 0)
    {
        RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    }

    // set PA8 in alternate function mode
    GPIOA->MODER &= ~GPIO_MODER_MODER8_0;
    GPIOA->MODER |= GPIO_MODER_MODER8_1;

    // set AF6 for PA8
    GPIOA->AFR[1] |= (6 << GPIO_AFRH_AFRH0_Pos);

    // enable clock access to TIM1 (APB2)
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    // set prescaler value for ~60Hz PWM frequency
    TIM1->PSC = 665;
    TIM1->ARR = 100 - 1;

    // fix duty cycle on 50%
    TIM1->CCR1 = 80;

    // set center aligned PWM mode
    TIM1->CR1 |= TIM_CR1_CMS_0;
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
    TIM1->CCMR1 |= TIM_CCMR1_OC1PE;

    // clear counter
    TIM1->CNT = 0;
}

void
pwm_run(void)
{
    // Ensure main output is enabled
    TIM1->BDTR |= TIM_BDTR_MOE;

    // Enable the output channel
    TIM1->CCER |= TIM_CCER_CC1E;

    // Enable the timer
    TIM1->CR1 |= TIM_CR1_CEN;
}

void
pwm_stop(void)
{
    // Disable the timer
    TIM1->CR1 &= ~TIM_CR1_CEN;

    // Disable the output channel
    TIM1->CCER &= ~TIM_CCER_CC1E;
}