# Singletons vs Objects

## Description
Most of the objects in the application are singletons which are considered harmful, due to reentrance violations and "thread" safety. But the are simple. Introducing object comes with series of problems - implementation leakage, complex object creation to name a few. There is an opaque pattern, but for now I know only how to use it by `malloc` function, which I want to avoid.

According to the singleton best practices they should be used at the minimum as possible, only on the "things" that are actually singe in the system, messaging quques, networking process, etc.

## Decision
There are some places where I could introduce objects:
* GPIOs
* L293 channels
* PWM (nice to have)
* Timer (nice to have)

There are some places where I coul use singletons:
* Dualshock2 communication process (networking?)
* SPI (there is only one SPI peripheral on both ATmega88PA and STM32F303x8)
* Vehicle (there is only one device :) )
* Motion (there is only one motion, but will use L293 channel objects )

## Alternatives
* Vehicle and motion as the objects as well caused huge implementation leakage

## Outcome
* More FLASH usage. 25.4% vs ~20% - no suprise here actually
* RAM stays still. ~10%
* Great unit test experiance!
