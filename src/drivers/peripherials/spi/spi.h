#ifndef _SPI_H
#define _SPI_H

#include <stdint.h>

void
spi_init_master(void);

void
spi_on_response_received_isr(uint8_t resposne) __attribute__((weak));

#endif