#include "vehicle.h"

// led is PB3
#define LED_PIN GPIO_ODR_3

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