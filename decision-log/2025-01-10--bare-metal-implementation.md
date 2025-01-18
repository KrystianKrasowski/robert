# Bare metal implementation or to HAL or not to HAL part 2.

## Description:
As I want to migrate to ARM processor and NOT to use HAL there I want to separate logic and drivers first. Then the only job would be to implement the drivers for another CPU architecture. 
* FLASH: 3050 bytes (37.2% Full)
* RAM: 392 bytes (38.3% Full)

## Decision
To simplify this process I want to get rid of AVRHAL dependency and implement bare-metal drivers without utils layer

## Outcome
* FLASH usage 1280 bytes (15.6% Full) - 1770 bytes less
* RAM usage 94 bytes (9.2% Full) - 298 bytes less

This is huge improvment