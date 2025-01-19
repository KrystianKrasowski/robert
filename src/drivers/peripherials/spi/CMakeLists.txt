add_library(spi INTERFACE spi.h)

target_include_directories(spi
    INTERFACE
        "./"
)

add_library(spi_atmega88pa spi_atmega88pa.c)

target_link_libraries(spi_atmega88pa
    INTERFACE
        spi
)