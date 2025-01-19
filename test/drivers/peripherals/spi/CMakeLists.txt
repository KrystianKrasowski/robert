target_link_libraries(spi_atmega88pa
    PUBLIC
        atmega88pa-stub
)

add_executable(spi_atmega88pa_test spi_atmega88pa_test.c)

target_include_directories(spi_atmega88pa_test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/test/include
)

target_link_libraries(spi_atmega88pa_test
    PRIVATE
        spi_atmega88pa
        unity
)

add_test(spi_atmega88pa_test spi_atmega88pa_test)