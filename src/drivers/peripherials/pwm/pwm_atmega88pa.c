#include "pwm.h"
#include <avr/io.h>
#include <stdint.h>

void
pwm_init(void)
{
    // set phase correct PWM on TIMER0
    TCCR0A |= (1 << WGM00);
    TCCR0A &= ~(1 << WGM01);
    TCCR0B &= ~(1 << WGM02);

    // set OC0A as output for non-inverting mode
    OC0A_DDR |= (1 << OC0A_BIT);

    // set duty cycle to fixed 85%
    OCR0A = 0xd9;
}

void
pwm_run(void)
{
    uint8_t tccr0a_mask = TCCR0A;
    uint8_t tccr0b_mask = TCCR0B;

    // set non-inverting mode on PWM channel A
    tccr0a_mask &= ~(1 << COM0A0);
    tccr0a_mask |= (1 << COM0A1);

    // set 256 TIMER0 prescaller
    // TODO: check if I could do this only for init operation
    tccr0b_mask &= ~(1 << CS00);
    tccr0b_mask &= ~(1 << CS01);
    tccr0b_mask |= (1 << CS02);

    // apply register values at once for performence
    TCCR0A = tccr0a_mask;
    TCCR0B = tccr0b_mask;
}

void
pwm_stop(void)
{
    // set disconnected mode on PWM channel A
    TCCR0A &= ~((1 << COM0A0) | (1 << COM0A1));

    // stop the timer
    // TODO: check if I cound do this only for init operation
    TCCR0B &= ~((1 << CS00) | (1 << CS01) | (1 << CS02));
}