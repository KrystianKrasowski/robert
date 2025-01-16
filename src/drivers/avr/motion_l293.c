#include "drivers/motion.h"
#include <avr/io.h>

#define LEFT_FRONT_A1_BIT  3
#define LEFT_FRONT_A2_BIT  2
#define LEFT_REAR_A1_BIT   5
#define LEFT_REAR_A2_BIT   4
#define RIGHT_FRONT_A1_BIT 0
#define RIGHT_FRONT_A2_BIT 1
#define RIGHT_REAR_A1_BIT  2
#define RIGHT_REAR_A2_BIT  3

static void
motion_gpio_init(void);

static void
motion_gpio_set(motion_direction_t direction,
                uint8_t volatile  *PORTx,
                uint8_t            a1,
                uint8_t            a2);

static void
motion_pwm_init(void);

static void
motion_pwm_run(void);

static void
motion_pwm_stop(void);

void
motion_init(void)
{
    motion_gpio_init();
    motion_pwm_init();
}

void
motion_apply(motion_t *self, bool is_soft_stop)
{
    motion_pwm_stop();

    motion_gpio_set(
        self->left_front, &PORTC, LEFT_FRONT_A1_BIT, LEFT_FRONT_A2_BIT);

    motion_gpio_set(
        self->right_front, &PORTD, RIGHT_FRONT_A1_BIT, RIGHT_FRONT_A2_BIT);

    motion_gpio_set(
        self->left_rear, &PORTC, LEFT_REAR_A1_BIT, LEFT_REAR_A2_BIT);

    motion_gpio_set(
        self->right_rear, &PORTD, RIGHT_REAR_A1_BIT, RIGHT_REAR_A2_BIT);

    if (!is_soft_stop)
    {
        motion_pwm_run();
    }
}

static void
motion_gpio_init(void)
{
    uint8_t ddrc_mask = DDRC;
    uint8_t ddrd_mask = DDRD;

    // set left front motor l293 channel pins as output
    ddrc_mask |= (1 << LEFT_FRONT_A1_BIT);
    ddrc_mask |= (1 << LEFT_FRONT_A2_BIT);

    // set right front motor l293 channel pins as output
    ddrd_mask |= (1 << RIGHT_FRONT_A1_BIT);
    ddrd_mask |= (1 << RIGHT_FRONT_A2_BIT);

    // set left rear motor l293 channel pins as output
    ddrc_mask |= (1 << LEFT_REAR_A1_BIT);
    ddrc_mask |= (1 << LEFT_REAR_A2_BIT);

    // set right rear motor l293 channel pins as output
    ddrd_mask |= (1 << RIGHT_REAR_A1_BIT);
    ddrd_mask |= (1 << RIGHT_REAR_A2_BIT);

    DDRC = ddrc_mask;
    DDRD = ddrd_mask;
}

static void
motion_pwm_init(void)
{
    // set phase correct PWM on TIMER0
    TCCR0A |= (1 << WGM00);
    TCCR0A &= ~(1 << WGM01);
    TCCR0B &= ~(1 << WGM02);

    // set OC0A as output for non-inverting mode
    OC0A_DDR |= (1 << OC0A_BIT);

    // set duty cycle to fixed 85%
    OCR0A = 0xd9;
}

static void
motion_pwm_run(void)
{
    // set non-inverting mode on PWM channel A
    TCCR0A &= ~(1 << COM0A0);
    TCCR0A |= (1 << COM0A1);

    // set 256 TIMER0 prescaller
    // TODO: check if I could do this only for init operation
    TCCR0B &= ~(1 << CS00);
    TCCR0B &= ~(1 << CS01);
    TCCR0B |= (1 << CS02);
}

static void
motion_pwm_stop(void)
{
    // set disconnected mode on PWM channel A
    TCCR0A &= ~((1 << COM0A0) | (1 << COM0A1));

    // stop the timer
    // TODO: check if I cound do this only for init operation
    TCCR0B &= ~((1 << CS00) | (1 << CS01) | (1 << CS02));
}

static void
motion_gpio_set(motion_direction_t direction,
                uint8_t volatile  *PORTx,
                uint8_t            a1,
                uint8_t            a2)
{
    switch (direction)
    {
        case MOTION_FORWARD:
            *PORTx &= ~(1 << a1);
            *PORTx |= (1 << a2);
            break;
        case MOTION_BACKWARD:
            *PORTx |= (1 << a1);
            *PORTx &= ~(1 << a2);
            break;
        case MOTION_NONE:
        default:
            *PORTx &= ~(1 << a1);
            *PORTx &= ~(1 << a2);
    }
}