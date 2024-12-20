#ifndef _ATMEGA88PA_INTERRUPT_H
#define _ATMEGA88PA_INTERRUPT_H

#define ISR(vector) void vector(void)

void
sei(void);

void
cli(void);

#endif