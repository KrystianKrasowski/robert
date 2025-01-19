#ifndef _TIMER_H
#define _TIMER_h

void
timer_init(void);

void
timer_compare_a_match_isr(void) __attribute__((weak));

void
timer_compare_b_match_isr(void) __attribute__((weak));

#endif