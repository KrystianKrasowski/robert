#include <stdint.h>

// GPIO - plain object with factory

typedef enum
{
    OGPIO_L293_MOTOR_LEFT_FRONT_A1,
} ogpio_pin_t;

typedef enum
{
    OGPIO_MODE_INPUT,
    OGPIO_MODE_OUTPUT,
} ogpio_mode_t;

typedef enum
{
    OGPIO_STATE_LOW,
    OGPIO_STATE_HIGH,
} ogpio_state_t;

typedef struct ogpio
{
    ogpio_pin_t const pin;
    ogpio_mode_t      mode;
    ogpio_state_t     state;
} ogpio_t;

ogpio_t
ogpio_create(ogpio_pin_t const pin)
{
    ogpio_t ogpio = {pin};

    switch (pin)
    {
        case OGPIO_L293_MOTOR_LEFT_FRONT_A1:
            ogpio.mode  = OGPIO_MODE_OUTPUT;
            ogpio.state = OGPIO_STATE_LOW;
            break;
    }

    return ogpio;
}

void
ogpio_init(ogpio_t *self)
{
    init_gpio_object(self);
    init_peripheral(self);
}

void
ogpio_set_state(ogpio_t *self, ogpio_state_t state)
{
    if (state != self->state)
    {
        self->state = state;
        set_peripheral_state(self);
    }
}

init_gpio_object(ogpio_t *self)
{
    switch (self->pin)
    {
        case OGPIO_L293_MOTOR_LEFT_FRONT_A1:
            self->mode  = OGPIO_MODE_OUTPUT;
            self->state = OGPIO_STATE_LOW;
            break;
    }
}

void
init_peripheral(ogpio_t *gpio)
{
    // _gpio = gpio_map[gpio->pin];

    // STM32
    // uint32_t rcc_ahbenr  = RCC->AHBENR;
    // uint32_t rcc_gpioxen = gpio_map[gpio->pin].rcc_gpioxen;
    // if (rcc_ahbenr & rcc_gpioxen)
    // {
    //     rcc_ahbenr |= rcc_gpioxenr;
    //     RCC->AHBENR = rcc_ahbenr;
    // }
    //
    // GPIO_TypeDef gpiox = _gpio.gpiox;
    // if (gpio->mode == OGPIO_MODE_OUTPUT)
    // {
    //     gpiox->MODER |= _gpio.mode_0;
    //     gpiox->MODER &= ~_gpio.mode_1;
    // }
    // else
    // {
    //     gpiox->MODER &= ~_gpio.mode_0;
    //     gpiox->MODER &= ~_gpio.mode_1;
    // }

    // Atmega
    // if (gpio->mode == OGPIO_MODE_OUTPUT)
    // {
    //     _gpio_map.ddrx |= (1 << _gpio.bit);
    // }
    // else
    // {
    //     _gpio_map.ddrx &= ~(1 << _gpio.bit);
    // }
}

void
set_peripheral_state(ogpio_t *gpio)
{
    // _gpio = gpio_map[gpio->pin];

    // STM32
    // GPIO_TypeDef gpiox = _gpio.gpiox;

    // if (gpio->state == OGPIO_STATE_LOW)
    // {

    //     gpiox->ODR &= ~(1 << _gpio.bit);
    // }
    // else
    // {
    //     gpiox->ODR |= (1 << _gpio_bit);
    // }

    // atmega
    // if (gpio->state == OGPIO_STATE_LOW)
    // {
    //     _gpio.portx &= ~(1 << _gpio.bit);
    // }
    // else
    // {
    //     _gpio.portx |= (1 << _gpio.bit);
    // }
}

// GPIO END -------------------------------------

// PWM ----------------
typedef struct pwm
{
    uint8_t prescaller;
} opwm_t;

void
opwm_stop(opwm_t *self)
{
}

// L293

typedef enum
{
    L293_DIRECTION_LEFT,
    L293_DIRECTION_RIGHT,
    L293_DIRECTION_NONE,
} l293_direction_t;

typedef struct l293_channel
{
    ogpio_t          a1;
    ogpio_t          a2;
    opwm_t           pwm;
    l293_direction_t direction;
} l293_channel_t;

void
l293_soft_stop(l293_channel_t *self)
{
    opwm_stop(&self->pwm);
}

void
l293_set(l293_channel_t *self, l293_direction_t direction)
{
}