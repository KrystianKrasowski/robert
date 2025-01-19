target_link_libraries(gpio_atmega88pa
    PUBLIC
        atmega88pa-stub
)

add_executable(gpio_atmega88pa_test gpio_atmega88pa_test.c)

target_include_directories(gpio_atmega88pa_test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/test/include
)

target_link_libraries(gpio_atmega88pa_test
    INTERFACE
        gpio
    PRIVATE
        gpio_atmega88pa
        unity
)

add_test(gpio_atmega88pa_test gpio_atmega88pa_test)