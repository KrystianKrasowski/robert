#include "avr/io.h"
#include "avr/stub.h"

uint8_t  PINB   = 0;
uint8_t  DDRB   = 0;
uint8_t  PORTB  = 0;
uint8_t  PINC   = 0;
uint8_t  DDRC   = 0;
uint8_t  PORTC  = 0;
uint8_t  PIND   = 0;
uint8_t  DDRD   = 0;
uint8_t  PORTD  = 0;
uint8_t  SPCR   = 0;
uint8_t  SPSR   = 0;
uint8_t  SPDR   = 0;
uint8_t  TCCR0A = 0;
uint8_t  TCCR0B = 0;
uint8_t  TCNT0  = 0;
uint8_t  OCR0A  = 0;
uint8_t  OCR0B  = 0;
uint8_t  TCCR1A = 0;
uint8_t  TCCR1B = 0;
uint8_t  TCCR1C = 0;
uint16_t TCNT1  = 0;
uint16_t ICR1   = 0;
uint16_t OCR1A  = 0;
uint16_t OCR1B  = 0;
uint8_t  TIMSK1 = 0;

static bool global_interrupts_enable = false;

void
sei()
{
    global_interrupts_enable = true;
}

void
cli()
{
    global_interrupts_enable = false;
}

bool
is_global_interrupts_enable(void)
{
    return global_interrupts_enable;
}