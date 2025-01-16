#include "drivers/command.h"
#include "drivers/motion.h"
#include "drivers/motion_mock.h"

static bool initialized = false;
static motion_t applied_motion = {};
static int apply_call_count = 0;

void
motion_init(void)
{
    initialized = true;
}

void
motion_apply(motion_t *self, bool is_soft_stop)
{
    applied_motion = *self;
    apply_call_count++;
}

bool
motion_mock_is_initialized(void)
{
    return initialized;
}

bool
motion_mock_verify_left_front(motion_direction_t direction)
{
    return applied_motion.left_front == direction;
}

bool
motion_mock_verify_right_front(motion_direction_t direction)
{
    return applied_motion.right_front == direction;
}

bool
motion_mock_verify_left_rear(motion_direction_t direction)
{
    return applied_motion.left_rear == direction;
}

bool
motion_mock_verify_right_rear(motion_direction_t direction)
{
    return applied_motion.right_rear == direction;
}

int
motion_mock_apply_call_count(void)
{
    return apply_call_count;
}

void
motion_mock_reset(void)
{
    initialized = false;
    apply_call_count = 0;
}