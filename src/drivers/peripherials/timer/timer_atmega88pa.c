#include "timer.h"
#include <avr/interrupt.h>
#include <avr/io.h>

void
timer_init(void)
{
    // configure timer1 in CTC mode and 8 prescaller
    TCCR1B |= (1 << WGM12) | (1 << CS11);

    // configure controller state read each 16 ms
    OCR1A = 16000;

    // configure controller read start delay for 200 us
    OCR1B = 200;

    // configure timer1 with interrupts on both channels a and b
    TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B);
}

ISR(TIMER1_COMPA_vect)
{
    timer_compare_a_match_isr();
}

ISR(TIMER1_COMPB_vect)
{
    timer_compare_b_match_isr();
}

__attribute__((weak)) void
timer_compare_a_match_isr(void)
{
}


__attribute__((weak)) void
timer_compare_b_match_isr(void)
{
}