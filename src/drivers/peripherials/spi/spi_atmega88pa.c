#include "spi.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void
spi_init_master(void)
{
    // slave select is configured as input with pull-up due to securing master
    // mode
    SS_DDR &= ~(1 << SS_BIT);
    SS_PORT |= (1 << SS_BIT);

    // configure necessary outputs for master mode - MOSI and clock
    MOSI_DDR |= (1 << MOSI_BIT);
    SCK_DDR |= (1 << SCK_BIT);

    // configure SPCR value
    uint8_t spcr_value = 0;
    uint8_t spsr_value = 0;

    // configure SPI interface in master mode
    spcr_value |= (1 << SPE) | (1 << MSTR);

    // configure SPI interrupts
    spcr_value |= (1 << SPIE);

    // configure lsb first order
    spcr_value |= (1 << DORD);

    // configure mode 3 of SPI
    // - clock idle on HIGH
    // - data shift on falling edge
    // - data sample on rising edge
    spcr_value |= (1 << CPOL);
    spcr_value |= (1 << CPHA);

    // configure spi clock speed prescaller to 32
    spcr_value &= ~(1 << SPR0);
    spcr_value |= (1 << SPR1);
    spsr_value |= (1 << SPI2X);

    // write to SPCR and SPSR as one operation due to performence optimaization
    SPCR = spcr_value;
    SPSR = spsr_value;
}

void
spi_transmit(uint8_t const request)
{
    SPDR = request;
}

ISR(SPI_STC_vect)
{
    spi_on_response_received_isr(SPDR);
}

__attribute__((weak)) void
spi_on_response_received_isr(uint8_t const resposne)
{
}