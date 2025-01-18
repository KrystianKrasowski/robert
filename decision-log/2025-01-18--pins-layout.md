# Which MCU pins would be in use?

## Description
Dedicate STM32F303K8T6 MCU pins purpose: SPI, and L293

## Outcome

SPI:
* PB5 - MOSI
* PB4 - MISO
* PB3 - SCK
* PA12 - Dualshock2 SS
* PB0 - TIM3_CH3 - Timer channel for communication delay
* PB1 - TIM3_CH4 - Timer channel for first byte delay

L293
* PA0 - GPIO for front left motor A1 pin
* PA1 - GPIO for front left motor A2 pin
* PA2 - GPIO for front right motor A1 pin
* PA3 - GPIO for front right motor A2 pin
* PA4 - GPIO for rear left motor A1 pin
* PA5 - GPIO for rear left motor A2 pin
* PA6 - GPIO for rear right motor A1 pin
* PA7 - GPIO for rear right motor A2 pin
* PA8 - TIM1_CH1 - Timer channel for PWM

## Alternatives
* Use dualshock2 ACK signal instead of timer delay - that would be actually better solution, but for the sake of the deadline and current "know how" I'll stick to the timers. Can be definitely something for further improvement