#include "infrared_pilot.h"
#include <avrhal/timer1.h>
#include <avrhal/timer1_interrupts.h>

volatile static uint8_t  _overflows      = 0;
volatile static uint8_t  _command_ready  = 0;
volatile static uint8_t  _captures_count = 0;
volatile static uint16_t _raw_cmd[33]    = {0};

void
infrared_pilot_init()
{
    hal_timer1_interrupts_t interrupts = {
        .timer_overflow = 1,
        .input_capture  = 1,
    };

    hal_timer1_interrupts_init(&interrupts);
    // 8MHz clock frequency is assumed here
    hal_timer1_run(HAL_TIMER_PRESCALLER_8);
}

infrared_pilot_command_t
infrared_pilot_read(void)
{
    if (_command_ready == 0)
    {
        return IRP_CMD_NREADY;
    }

    uint8_t i, code = 0;

    for (i = 0; i < 33; i++)
    {
        // TODO: Command validation
        if (i >= 17 && i <= 24)
        {
            uint8_t index = 7 - (i - 17);

            if (_raw_cmd[i] <= INFRARED_PILOT_WIDTH_LOGIC_0)
            {
                code |= (0 << index);
            }

            if (_raw_cmd[i] > INFRARED_PILOT_WIDTH_LOGIC_0 &&
                _raw_cmd[i] <= INFRARED_PILOT_WIDTH_LOGIC_1)
            {
                code |= (1 << index);
            }
        }
    }

    return code;
}

void
infrared_pilot_release(void)
{
    for (uint8_t i = 0; i < 33; i++)
    {
        _raw_cmd[i] = 0;
    }
    _command_ready  = 0;
    _captures_count = 0;
    _overflows      = 0;
}

void
hal_timer1_input_capture_isr(const uint16_t value)
{
    hal_timer1_set(0);
    ++_captures_count;
    _overflows = 0;

    if (_captures_count > 1 && !_command_ready)
    {
        uint8_t index   = _captures_count - 2;
        _raw_cmd[index] = value;

        if (index == 32)
        {
            _command_ready = 1;
        }
    }
}

void
hal_timer1_timer_overflow_isr(void)
{
    ++_overflows;
    if (_overflows > 1)
    {
        infrared_pilot_release();
    }
}
