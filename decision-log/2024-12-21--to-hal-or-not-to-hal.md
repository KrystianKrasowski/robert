# To HAL or not to HAL

## Description:
I considered refactoring to bare-metal implementation due to concerns about flash and ram usage and overall execution speed. As for now the consuption is:
* FLASH: 3050 bytes (37.2% Full)
* RAM: 392 bytes (38.3% Full)

## Outcome
I ended up with similar solution developing a util code layer. It was simpler than HAL but causes much complicated driver implementation. As for the resources consumption there was 7% profit.

## Decision
I'll stick to the HAL library.
* 7% is not significant
* The code is more reusable
* The implementation is more descriptive

## Sources
* `feature/bare-metal`