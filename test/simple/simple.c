
#include <stdio.h>
#include "unity.h"

void
should_pass()
{
    TEST_ASSERT_TRUE(0);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_pass);
    return UNITY_END();
}