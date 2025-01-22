#ifndef _SPI_H
#define _SPI_H

#include <stdbool.h>
#include <stdint.h>

void
spi_init_master(void);

// void
// spi_transmit(uint8_t const request);

bool
spi_transmit(uint8_t *request, uint8_t size);

bool
spi_receive(uint8_t *response, uint8_t size);

void
spi_on_response_received_isr(uint8_t const resposne) __attribute__((weak));

#endif