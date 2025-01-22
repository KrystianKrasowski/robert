#include "vehicle.h"

int
main(void)
{
    vehicle_init();

    while (1)
    {
        vehicle_run();
    }

    return 0;
}