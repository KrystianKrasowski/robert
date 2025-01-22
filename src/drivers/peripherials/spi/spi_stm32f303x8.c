#include "spi.h"
#include "stm32f3xx.h"

#define GPIO_MODER_AF 2
#define BUFFER_SIZE   10

// TODO: a struct would be nice here
static volatile uint8_t tx_buffer[BUFFER_SIZE];
static volatile uint8_t rx_buffer[BUFFER_SIZE];
static volatile uint8_t tx_index          = 0;
static volatile uint8_t rx_index          = 0;
static volatile uint8_t data_size         = 0;
static volatile bool    transfer_complete = true;

void
spi_init_master(void)
{
    // enable AHB clock access to GPIOB
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // enable APB2 clock access to SPI
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // set PB3 mode to alternate function
    GPIOB->MODER |= (GPIO_MODER_AF << GPIO_MODER_MODER3_Pos);

    // set PB4 mode to alternate function
    GPIOB->MODER |= (GPIO_MODER_AF << GPIO_MODER_MODER4_Pos);

    // set PB5 mode to alternate function
    GPIOB->MODER |= (GPIO_MODER_AF << GPIO_MODER_MODER5_Pos);

    // set PB3 alternate function to SPI SCK (AF5)
    GPIOB->AFR[0] |= (5 << GPIO_AFRL_AFRL3_Pos);

    // set PB4 altrnate function to SPI MISO (AF5)
    GPIOB->AFR[0] |= (5 << GPIO_AFRL_AFRL4_Pos);

    // set PB5 alternate function to SPI MOSI (AF5)
    GPIOB->AFR[0] |= (5 << GPIO_AFRL_AFRL5_Pos);

    // set SPI bus speed to 250kHz (8MHz / 32psc)
    SPI1->CR1 |= (4 << SPI_CR1_BR_Pos);

    // set mode 3
    SPI1->CR1 |= (SPI_CR1_CPHA | SPI_CR1_CPOL);

    // set fullduplex communication
    SPI1->CR1 &= ~SPI_CR1_RXONLY;

    // set LSB first
    SPI1->CR1 |= SPI_CR1_LSBFIRST;

    // set software slave management
    SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;

    // set SPI in master mode
    SPI1->CR1 |= SPI_CR1_MSTR;

    // CR2
    // set data lenght to 8bit (DS: 0111)
    SPI1->CR2 |= (7 << SPI_CR2_DS_Pos);

    // configure SSOE - it might be the pull-up issue
    // enable interrupts
    SPI1->CR2 |= SPI_CR2_TXEIE | SPI_CR2_RXNEIE;

    // trigger interrupt wher RX buffer is 8bit long
    SPI1->CR2 |= SPI_CR2_FRXTH;

    // enable SPI
    SPI1->CR1 |= SPI_CR1_SPE;

    // set NVIC for interrupts
    NVIC_EnableIRQ(SPI1_IRQn);
}

bool
spi_transmit(uint8_t *request, uint8_t size)
{
    if (transfer_complete)
    {
        // fill the transmit buffer
        for (uint8_t i = 0; i < size; i++)
        {
            tx_buffer[i] = request[i];
        }

        // initialize the communication
        data_size         = size;
        tx_index          = 0;
        transfer_complete = false;

        // start transmission by enabling the interrupt
        SPI1->CR2 |= SPI_CR2_TXEIE;

        return true;
    }
    else
    {
        return false;
    }
}

bool
spi_receive(uint8_t *response, uint8_t size)
{
    if (transfer_complete)
    {
        for (uint8_t i = 0; i < size; i++)
        {
            response[i] = rx_buffer[i];
        }

        return true;
    }
    else
    {
        return false;
    }
}

void
SPI1_IRQHandler(void)
{
    if (SPI1->SR & SPI_SR_TXE)
    {
        if (tx_index < data_size)
        {
            SPI1->DR = tx_buffer[tx_index++];
        }
        else
        {
            // all data transmitted, disable interrupt
            SPI1->CR2 &= ~SPI_CR2_TXEIE;
        }
    }

    if (SPI1->SR & SPI_SR_RXNE)
    {
        rx_buffer[rx_index++] = SPI1->DR;
        if (rx_index >= data_size)
        {
            transfer_complete = true;
        }
    }
}