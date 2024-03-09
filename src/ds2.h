#ifndef _DUALSHOCK2
#define _DUALSHOCK2

#include <stdint.h>

typedef enum
{
    DS2_NONE            = 0,
    DS2_BUTTON_SELECT   = 1,
    DS2_BUTTON_L3       = 2,
    DS2_BUTTON_R3       = 4,
    DS2_BUTTON_START    = 8,
    DS2_BUTTON_UP       = 16,
    DS2_BUTTON_RIGHT    = 32,
    DS2_BUTTON_DOWN     = 64,
    DS2_BUTTON_LEFT     = 128,
    DS2_BUTTON_L2       = 256,
    DS2_BUTTON_R2       = 512,
    DS2_BUTTON_L1       = 1024,
    DS2_BUTTON_R1       = 2048,
    DS2_BUTTON_TRIANGLE = 4096,
    DS2_BUTTON_CIRCLE   = 8192,
    DS2_BUTTON_CROSS    = 16384,
    DS2_BUTTON_SQUARE   = 32768,
} ds2_button_t;

void
ds2_init(void);

uint16_t
ds2_read(void);

#endif
