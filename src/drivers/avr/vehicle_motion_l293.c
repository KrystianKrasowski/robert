#include "vehicle_motion_port.h"
#include <avr/io.h>

#define MOTOR_LEFT_FRONT_A1_BIT  3
#define MOTOR_LEFT_FRONT_A2_BIT  2
#define MOTOR_LEFT_REAR_A1_BIT   5
#define MOTOR_LEFT_REAR_A2_BIT   4
#define MOTOR_RIGHT_FRONT_A1_BIT 0
#define MOTOR_RIGHT_FRONT_A2_BIT 1
#define MOTOR_RIGHT_REAR_A1_BIT  2
#define MOTOR_RIGHT_REAR_A2_BIT  3

static void
vehicle_motion_gpio_init(void);

static void
vehicle_motion_gpio_set(vehicle_motion_t  motion,
                        uint8_t volatile *PORTx,
                        uint8_t           a1,
                        uint8_t           a2);

static void
vehicle_motion_pwm_init(void);

static void
vehicle_motion_pwm_run(void);

static void
vehicle_motion_pwm_stop(void);

void
vehicle_motion_init(void)
{
    vehicle_motion_gpio_init();
    vehicle_motion_pwm_init();
}

void
vehicle_motion_apply(vehicle_t *self)
{
    vehicle_motion_gpio_set(self->motor_left_front,
                            &PORTC,
                            MOTOR_LEFT_FRONT_A1_BIT,
                            MOTOR_LEFT_FRONT_A2_BIT);

    vehicle_motion_gpio_set(self->motor_right_front,
                            &PORTD,
                            MOTOR_RIGHT_FRONT_A1_BIT,
                            MOTOR_RIGHT_FRONT_A2_BIT);

    vehicle_motion_gpio_set(self->motor_left_rear,
                            &PORTC,
                            MOTOR_LEFT_REAR_A1_BIT,
                            MOTOR_LEFT_REAR_A2_BIT);

    vehicle_motion_gpio_set(self->motor_right_rear,
                            &PORTD,
                            MOTOR_RIGHT_REAR_A1_BIT,
                            MOTOR_RIGHT_REAR_A2_BIT);

    if (self->current_command == COMMAND_SOFT_STOP)
    {
        vehicle_motion_pwm_stop();
    }

    else
    {
        vehicle_motion_pwm_run();
    }
}

static void
vehicle_motion_gpio_init(void)
{
    // set left front motor l293 channel pins as output
    DDRC |= (1 << MOTOR_LEFT_FRONT_A1_BIT);
    DDRC |= (1 << MOTOR_LEFT_FRONT_A2_BIT);

    // set right front motor l293 channel pins as output
    DDRD |= (1 << MOTOR_RIGHT_FRONT_A1_BIT);
    DDRD |= (1 << MOTOR_RIGHT_FRONT_A2_BIT);

    // set left rear motor l293 channel pins as output
    DDRC |= (1 << MOTOR_LEFT_REAR_A1_BIT);
    DDRC |= (1 << MOTOR_LEFT_REAR_A2_BIT);

    // set right rear motor l293 channel pins as output
    DDRD |= (1 << MOTOR_RIGHT_REAR_A1_BIT);
    DDRD |= (1 << MOTOR_RIGHT_REAR_A2_BIT);
}

static void
vehicle_motion_pwm_init(void)
{
    // set phase correct PWM on TIMER0
    TCCR0A |= (1 << WGM00);
    TCCR0A &= ~(1 << WGM01);
    TCCR0B &= ~(1 << WGM02);

    // set OC0A as output for non-inverting mode
    OC0A_DDR = (1 << OC0A_BIT);

    // set duty cycle to fixed 75%
    OCR0A = 0xbf;
}

static void
vehicle_motion_pwm_run(void)
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
vehicle_motion_pwm_stop(void)
{
    // set disconnected mode on PWM channel A
    TCCR0A &= ~((1 << COM0A0) | (1 << COM0A1));

    // stop the timer
    // TODO: check if I cound do this only for init operation
    TCCR0B &= ~((1 << CS00) | (1 << CS01) | (1 << CS02));
}

static void
vehicle_motion_gpio_set(vehicle_motion_t  motion,
                        uint8_t volatile *PORTx,
                        uint8_t           a1,
                        uint8_t           a2)
{
    switch (motion)
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