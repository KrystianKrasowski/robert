#include "dualshock2.h"
#include "unity_config.h"
#include <avr/io.h>
#include <unity.h>

void
setUp(void)
{
    DDRB   = 0;
    PORTB  = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
    SPCR   = 0;
    SPSR   = 0;
    SPDR   = 0;
}

void
tearDown(void)
{
}

void
should_set_dualshock2_attention_pin_as_output_and_high(void)
{
    // when
    dualshock2_init();

    // then
    TEST_ASSERT_BIT_HIGH(DDB1, DDRB);
    TEST_ASSERT_BIT_HIGH(PORTB1, PORTB);
}

void
should_set_timer1_in_ctc_mode(void)
{
    // when
    dualshock2_init();

    // then
    TEST_ASSERT_FALSE(TCCR1A);
    TEST_ASSERT_BIT_HIGH(WGM12, TCCR1B);
}

void
should_run_timer1_with_8_prescaller(void)
{
    // when
    dualshock2_init();

    // then
    TEST_ASSERT_BIT_LOW(CS12, TCCR1B);
    TEST_ASSERT_BIT_LOW(CS10, TCCR1B);
    TEST_ASSERT_BIT_HIGH(CS11, TCCR1B);
}

void
should_set_timer1_channels_resolution()
{
    // when
    dualshock2_init();

    // then
    TEST_ASSERT_EQUAL(16000, OCR1A);
    TEST_ASSERT_EQUAL(200, OCR1B);
}

void
should_enable_output_compare_interrupt_on_timer1_channels_a_b(void)
{
    // when
    dualshock2_init();

    // then
    TEST_ASSERT_BIT_HIGH(OCIE1A, TIMSK1);
    TEST_ASSERT_BIT_HIGH(OCIE1B, TIMSK1);
}

void
should_set_spi_in_master_mode(void)
{
    // when
    dualshock2_init();

    // then
    TEST_ASSERT_BIT_LOW(SS_BIT, SS_DDR);
    TEST_ASSERT_BIT_HIGH(SS_BIT, SS_PORT);
    TEST_ASSERT_BIT_HIGH(MOSI_BIT, MOSI_DDR);
    TEST_ASSERT_BIT_HIGH(SCK_BIT, SCK_DDR);
    TEST_ASSERT_BIT_HIGH(SPE, SPCR);
    TEST_ASSERT_BIT_HIGH(MSTR, SPCR);
}

void
should_set_spi_interrupts_enabled(void)
{
    // when
    dualshock2_init();

    // then
    TEST_ASSERT_BIT_HIGH(SPIE, SPCR);
}

void
should_set_spi_order_lsb_first(void)
{
    // when
    dualshock2_init();

    // then
    TEST_ASSERT_BIT_HIGH(DORD, SPCR);
}

void
should_set_spi_clock_polarity_as_falling_rising(void)
{
    // when
    dualshock2_init();

    // then
    TEST_ASSERT_BIT_HIGH(CPOL, SPCR);
}

void
should_set_spi_clock_phase_as_setup_sample(void)
{
    // when
    dualshock2_init();

    // then
    TEST_ASSERT_BIT_HIGH(CPHA, SPCR);
}

void
should_set_spi_clock_prescaller_as_32(void)
{
    // when
    dualshock2_init();

    // then
    TEST_ASSERT_BIT_HIGH(SPR1, SPCR);
    TEST_ASSERT_BIT_LOW(SPR0, SPCR);
    TEST_ASSERT_BIT_HIGH(SPI2X, SPSR);
}

void
should_pull_ds2_attention_pin_low_on_communication_start(void)
{
    // given
    dualshock2_handle_request_prepare_isr();

    // when
    uint16_t cmd = dualshock2_read();

    // then
    TEST_ASSERT_BIT_LOW(DDB1, PORTB);
    TEST_ASSERT_EQUAL_HEX8(DS2_NONE, cmd);
}

void
should_put_data_byte_on_transmit(void)
{
    // given
    dualshock2_handle_request_prepare_isr();
    dualshock2_handle_request_transmit_isr();

    // when
    // when
    uint16_t cmd = dualshock2_read();

    // then
    TEST_ASSERT_EQUAL_HEX8(0x01, SPDR);
}

void
should_read_control_command(uint8_t  response_sequence[],
                            uint16_t expected_command)
{
    // given
    dualshock2_handle_request_prepare_isr();
    dualshock2_handle_request_transmit_isr();

    for (int i = 0; i < 9; i++)
    {
        dualshock2_read();
        dualshock2_handle_response_isr(response_sequence[i]);
    }

    // when
    uint16_t cmd = dualshock2_read();

    // then
    TEST_ASSERT_EQUAL(expected_command, cmd);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_set_dualshock2_attention_pin_as_output_and_high);
    RUN_TEST(should_set_timer1_in_ctc_mode);
    RUN_TEST(should_run_timer1_with_8_prescaller);
    RUN_TEST(should_enable_output_compare_interrupt_on_timer1_channels_a_b);
    RUN_TEST(should_set_spi_in_master_mode);
    RUN_TEST(should_set_spi_interrupts_enabled);
    RUN_TEST(should_set_spi_order_lsb_first);
    RUN_TEST(should_set_spi_clock_polarity_as_falling_rising);
    RUN_TEST(should_set_spi_clock_phase_as_setup_sample);
    RUN_TEST(should_set_spi_clock_prescaller_as_32);
    RUN_TEST(should_pull_ds2_attention_pin_low_on_communication_start);
    RUN_TEST(should_put_data_byte_on_transmit);

    RUN_PARAM_TEST(
        should_read_control_command,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
        DS2_NONE);

    RUN_PARAM_TEST(
        should_read_control_command,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff},
        DS2_SELECT);

    RUN_PARAM_TEST(
        should_read_control_command,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff},
        DS2_L3);

    RUN_PARAM_TEST(
        should_read_control_command,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff},
        DS2_R3);

    RUN_PARAM_TEST(
        should_read_control_command,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff},
        DS2_START);

    RUN_PARAM_TEST(
        should_read_control_command,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff},
        DS2_UP);

    RUN_PARAM_TEST(
        should_read_control_command,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff},
        DS2_RIGHT);

    RUN_PARAM_TEST(
        should_read_control_command,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff},
        DS2_DOWN);

    RUN_PARAM_TEST(
        should_read_control_command,
        (uint8_t[]){0xff, 0x41, 0x5a, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff},
        DS2_LEFT);

    RUN_PARAM_TEST(
        should_read_control_command,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff},
        DS2_L2);

    RUN_PARAM_TEST(
        should_read_control_command,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff},
        DS2_R2);

    RUN_PARAM_TEST(
        should_read_control_command,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff},
        DS2_L1);

    RUN_PARAM_TEST(
        should_read_control_command,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff},
        DS2_R1);

    RUN_PARAM_TEST(
        should_read_control_command,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff},
        DS2_TRIANGLE);

    RUN_PARAM_TEST(
        should_read_control_command,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff},
        DS2_CIRCLE);

    RUN_PARAM_TEST(
        should_read_control_command,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff},
        DS2_CROSS);

    RUN_PARAM_TEST(
        should_read_control_command,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff},
        DS2_SQUARE);

    return UNITY_END();
}