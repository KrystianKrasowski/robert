#include "command.h"
#include "timer.h"

static volatile int i = 0;

static command_t sequence[20] =
    {
        COMMAND_MOVE_FACE_FORWARD,
        COMMAND_MOVE_FACE_BACKWARD,
        COMMAND_MOVE_SIDE_RIGHT,
        COMMAND_MOVE_SIDE_LEFT,
        COMMAND_MOVE_DIAG_FORWARD_RIGHT,
        COMMAND_MOVE_DIAG_FORWARD_LEFT,
        COMMAND_MOVE_DIAG_BACKWARD_RIGHT,
        COMMAND_MOVE_DIAG_BACKWARD_LEFT,
        COMMAND_ROTATE_SIDE_RIGHT_FORWARD,
        COMMAND_ROTATE_SIDE_LEFT_FORWARD,
        COMMAND_ROTATE_SIDE_RIGHT_BACKWARD,
        COMMAND_ROTATE_SIDE_LEFT_BACKWARD,
        COMMAND_ROTATE_RIGHT,
        COMMAND_ROTATE_LEFT,
        COMMAND_ROTATE_FACE_FRONT_RIGHT,
        COMMAND_ROTATE_FACE_FRONT_LEFT,
        COMMAND_ROTATE_FACE_REAR_RIGHT,
        COMMAND_ROTATE_FACE_REAR_LEFT,
        COMMAND_SOFT_STOP,
        COMMAND_HARD_STOP,
};

static volatile int index = 0;

void
command_init(void)
{
    timer_init();
}

command_t
command_receive(void)
{
    return sequence[index];
}

void
timer_compare_a_match_isr(void)
{
    index++;
    
    if (index == 20)
    {
        index = 0;
    }
}