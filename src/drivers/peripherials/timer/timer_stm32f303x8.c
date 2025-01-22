#include "stm32f3xx.h"
#include "timer.h"

void
timer_init(void)
{
    // set clock access to TIM3
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // set compare match every 0.5s on channel 3
    TIM3->PSC  = 8 - 1;
    TIM3->ARR  = 16000 - 1;
    TIM3->CCR3 = 16000;
    TIM3->CCR4 = 200;

    // enable the timer
    TIM3->CR1 |= TIM_CR1_CEN;

    // enable capture/compare interrupt for channel 3
    TIM3->DIER |= TIM_DIER_CC3IE;
    TIM3->DIER |= TIM_DIER_CC4IE;

    // enable TIM3 IRQ in NVIC
    NVIC_EnableIRQ(TIM3_IRQn);
    NVIC_SetPriority(TIM3_IRQn, 6);
}

void
TIM3_IRQHandler(void)
{
    if (TIM3->SR & TIM_SR_CC3IF)
    {
        TIM3->SR &= ~TIM_SR_CC3IF;
        timer_compare_a_match_isr();
    }

    if (TIM3->SR & TIM_SR_CC4IF)
    {
        TIM3->SR &= ~TIM_SR_CC4IF;
        timer_compare_b_match_isr();
    }
}

__attribute__((weak)) void
timer_compare_a_match_isr(void)
{
}

__attribute__((weak)) void
timer_compare_b_match_isr(void)
{
}