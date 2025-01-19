add_library(gpio INTERFACE gpio.h)

target_include_directories(gpio
    INTERFACE
        "./"
)

add_library(gpio_atmega88pa STATIC gpio_atmega88pa.c)

target_link_libraries(gpio_atmega88pa INTERFACE gpio)