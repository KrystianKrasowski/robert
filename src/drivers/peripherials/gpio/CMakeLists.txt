add_library(gpio INTERFACE gpio.h)

target_include_directories(gpio
    INTERFACE
        "./"
)

if(TARGET_ARCH STREQUAL "atmega88pa" OR TARGET_ARCH STREQUAL "test")
    add_library(gpio_atmega88pa STATIC gpio_atmega88pa.c)
    target_link_libraries(gpio_atmega88pa INTERFACE gpio)
endif()

if(TARGET_ARCH STREQUAL "stm32f303x8")
    add_library(gpio_stm32f303x8 STATIC gpio_stm32f303x8.c)

    target_link_libraries(gpio_stm32f303x8 
        INTERFACE gpio
        PRIVATE stm32f303x8
    )
endif()