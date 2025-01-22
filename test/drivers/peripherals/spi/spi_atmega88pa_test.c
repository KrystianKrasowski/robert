#include "spi.h"
#include "unity.h"
#include "unity_config.h"
#include <avr/io.h>

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_init_spi_in_master_mode(void)
{
    // when
    spi_init_master();

    // then
    TEST_ASSERT_BIT_LOW(SS_BIT, SS_DDR);
    TEST_ASSERT_BIT_HIGH(SS_BIT, SS_PORT);
    TEST_ASSERT_BIT_HIGH(MOSI_BIT, MOSI_DDR);
    TEST_ASSERT_BIT_HIGH(SCK_BIT, SCK_DDR);
    TEST_ASSERT_BIT_HIGH(SPE, SPCR);
    TEST_ASSERT_BIT_HIGH(MSTR, SPCR);
}

void
should_init_spi_with_interrupts_enabled(void)
{
    // when
    spi_init_master();

    // then
    TEST_ASSERT_BIT_HIGH(SPIE, SPCR);
}

void
should_init_spi_order_lsb_first(void)
{
    // when
    spi_init_master();

    // then
    TEST_ASSERT_BIT_HIGH(DORD, SPCR);
}

void
should_init_spi_in_mode_3(void)
{
    // when
    spi_init_master();

    // then
    TEST_ASSERT_BIT_HIGH(CPOL, SPCR);
    TEST_ASSERT_BIT_HIGH(CPHA, SPCR);
}

void
should_init_spi_clock_with_32_prescaller(void)
{
    // when
    spi_init_master();

    // then
    TEST_ASSERT_BIT_HIGH(SPR1, SPCR);
    TEST_ASSERT_BIT_LOW(SPR0, SPCR);
    TEST_ASSERT_BIT_HIGH(SPI2X, SPSR);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_init_spi_in_master_mode);
    RUN_TEST(should_init_spi_with_interrupts_enabled);
    RUN_TEST(should_init_spi_order_lsb_first);
    RUN_TEST(should_init_spi_in_mode_3);
    RUN_TEST(should_init_spi_clock_with_32_prescaller);
    return UNITY_END();
}