add_library(gpio_mock STATIC gpio_mock.h gpio_mock.c)

target_include_directories(gpio_mock
    PUBLIC
        "./"
)

target_link_libraries(gpio_mock
    PUBLIC
        gpio
)