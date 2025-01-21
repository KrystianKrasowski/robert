#include "command.h"
#include "timer.h"

static volatile int i = 0;

void
command_init(void)
{
    timer_init();
}

command_t
command_receive(void)
{
    if (i == 0)
    {
        return COMMAND_ROTATE_FACE_FRONT_LEFT;
    }
    else
    {
        return COMMAND_ROTATE_FACE_FRONT_RIGHT;
    }
}

void
timer_compare_a_match_isr(void)
{
    if (i == 0)
    {
        i = 1;
    }
    else
    {
        i = 0;
    }
}