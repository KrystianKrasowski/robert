#include "vehicle.h"
#include <avr/interrupt.h>

int
main(void)
{
    sei();
    vehicle_init();

    while (1)
    {
        vehicle_run();
    }

    return 0;
}