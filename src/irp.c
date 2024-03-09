#ifndef M_COMM
#define M_COMM 1
#endif

#if M_COMM == 1

#include "irp.h"
#include <avrhal/t1int.h>
#include <avrhal/t1nrm.h>

volatile static uint8_t  _overflows      = 0;
volatile static uint8_t  _command_ready  = 0;
volatile static uint8_t  _captures_count = 0;
volatile static uint16_t _raw_cmd[33]    = {0};

void
irp_init()
{
    hal_t1int_cfg_t config = {.timer_overflow = 1, .input_capture = 1};

    hal_t1int_configure(&config);
    // 8MHz clock frequency is assumed here
    hal_t1nrm_run(HAL_TIMER_PRESCALLER_8);
}

irp_command_t
irp_read(void)
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

            if (_raw_cmd[i] <= IR_WIDTH_LOGIC_0)
            {
                code |= (0 << index);
            }

            if (_raw_cmd[i] > IR_WIDTH_LOGIC_0 &&
                _raw_cmd[i] <= IR_WIDTH_LOGIC_1)
            {
                code |= (1 << index);
            }
        }
    }

    return code;
}

void
irp_release(void)
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
hal_t1int_on_input_capture(const uint16_t value)
{
    hal_t1nrm_set(0);
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
hal_t1int_on_timer_overflow(void)
{
    ++_overflows;
    if (_overflows > 1)
    {
        irp_release();
    }
}

#endif
