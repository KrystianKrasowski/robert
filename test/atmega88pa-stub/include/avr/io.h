#ifndef _ATMEGA88PA_IO_H
#define _ATMEGA88PA_IO_H

#include <stdint.h>

extern uint8_t PINB;
#define PINB0 0
#define PINB1 1
#define PINB2 2
#define PINB3 3
#define PINB4 4
#define PINB5 5
#define PINB6 6
#define PINB7 7

extern uint8_t DDRB;
#define DDB0 0
#define DDB1 1
#define DDB2 2
#define DDB3 3
#define DDB4 4
#define DDB5 5
#define DDB6 6
#define DDB7 7

extern uint8_t PORTB;
#define PORTB0 0
#define PORTB1 1
#define PORTB2 2
#define PORTB3 3
#define PORTB4 4
#define PORTB5 5
#define PORTB6 6
#define PORTB7 7

extern uint8_t PINC;
#define PINC0 0
#define PINC1 1
#define PINC2 2
#define PINC3 3
#define PINC4 4
#define PINC5 5
#define PINC6 6

extern uint8_t DDRC;
#define DDC0 0
#define DDC1 1
#define DDC2 2
#define DDC3 3
#define DDC4 4
#define DDC5 5
#define DDC6 6

extern uint8_t PORTC;
#define PORTC0 0
#define PORTC1 1
#define PORTC2 2
#define PORTC3 3
#define PORTC4 4
#define PORTC5 5
#define PORTC6 6

extern uint8_t PIND;
#define PIND0 0
#define PIND1 1
#define PIND2 2
#define PIND3 3
#define PIND4 4
#define PIND5 5
#define PIND6 6
#define PIND7 7

extern uint8_t DDRD;
#define DDD0 0
#define DDD1 1
#define DDD2 2
#define DDD3 3
#define DDD4 4
#define DDD5 5
#define DDD6 6
#define DDD7 7

extern uint8_t PORTD;
#define PORTD0 0
#define PORTD1 1
#define PORTD2 2
#define PORTD3 3
#define PORTD4 4
#define PORTD5 5
#define PORTD6 6
#define PORTD7 7

#define SS_DDR  DDRB
#define SS_PORT PORTB
#define SS_PIN  PINB
#define SS_BIT  2

#define MOSI_DDR  DDRB
#define MOSI_PORT PORTB
#define MOSI_PIN  PINB
#define MOSI_BIT  3

#define MISO_DDR  DDRB
#define MISO_PORT PORTB
#define MISO_PIN  PINB
#define MISO_BIT  4

#define SCK_DDR  DDRB
#define SCK_PORT PORTB
#define SCK_PIN  PINB
#define SCK_BIT  5

extern uint8_t SPCR;
#define SPR0 0
#define SPR1 1
#define CPHA 2
#define CPOL 3
#define MSTR 4
#define DORD 5
#define SPE 6
#define SPIE 7

extern uint8_t SPSR;
#define SPI2X 0
#define WCOL 6
#define SPIF 7

extern uint8_t SPDR;

extern uint8_t TCCR0A;
#define WGM00 0
#define WGM01 1
#define COM0B0 4
#define COM0B1 5
#define COM0A0 6
#define COM0A1 7

extern uint8_t TCCR0B;
#define CS00 0
#define CS01 1
#define CS02 2
#define WGM02 3
#define FOC0B 6
#define FOC0A 7

extern uint8_t TCNT0;
extern uint8_t OCR0A;
extern uint8_t OCR0B;

#define OC0A_DDR   DDRD
#define OC0A_PORT  PORTD
#define OC0A_PIN   PIND
#define OC0A_BIT   6

#define OC0B_DDR   DDRD
#define OC0B_PORT  PORTD
#define OC0B_PIN   PIND
#define OC0B_BIT   5

extern uint8_t TCCR1A;
#define WGM10 0
#define WGM11 1
#define COM1B0 4
#define COM1B1 5
#define COM1A0 6
#define COM1A1 7

extern uint8_t TCCR1B;
#define CS10 0
#define CS11 1
#define CS12 2
#define WGM12 3
#define WGM13 4
#define ICES1 6
#define ICNC1 7

extern uint8_t TCCR1C;
#define FOC1B 6
#define FOC1A 7

extern uint16_t TCNT1;
extern uint16_t ICR1;
extern uint16_t OCR1A;
extern uint16_t OCR1B;

extern uint8_t TIMSK1;
#define TOIE1 0
#define OCIE1A 1
#define OCIE1B 2
#define ICIE1 5

#define OC1A_DDR   DDRB
#define OC1A_PORT  PORTB
#define OC1A_PIN   PINB
#define OC1A_BIT   1
#define OC1B_DDR   DDRB
#define OC1B_PORT  PORTB
#define OC1B_PIN   PINB
#define OC1B_BIT   2

#endif