add_executable(dualshock2_test dualshock2_test.c)

target_include_directories(dualshock2_test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/test/include
)

target_link_libraries(dualshock2_test
    PRIVATE
        dualshock2
        gpio_atmega88pa
        timer_atmega88pa
        spi_atmega88pa
        atmega88pa-stub
        unity
)

add_test(dualshock2_test dualshock2_test)