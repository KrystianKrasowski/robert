add_library(spi INTERFACE spi.h)

target_include_directories(spi
    INTERFACE
        "./"
)

if(TARGET_ARCH STREQUAL "atmega88pa" OR TARGET_ARCH STREQUAL "test")
    add_library(spi_atmega88pa spi_atmega88pa.c)
    target_link_libraries(spi_atmega88pa INTERFACE spi)
endif()

if(TARGET_ARCH STREQUAL "stm32f303x8" OR TARGET_ARCH STREQUAL "test")
    add_library(spi_stm32f303x8 spi_stm32f303x8.c)
    target_link_libraries(spi_stm32f303x8 
        INTERFACE spi
        PRIVATE stm32f303x8
    )
endif()