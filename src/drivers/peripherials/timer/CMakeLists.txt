add_library(timer INTERFACE timer.h)

target_include_directories(timer
    INTERFACE
        "./"
)

if(TARGET_ARCH STREQUAL "atmega88pa" OR TARGET_ARCH STREQUAL "test")
    add_library(timer_atmega88pa STATIC timer_atmega88pa.c)
    target_link_libraries(timer_atmega88pa INTERFACE timer)
endif()

if(TARGET_ARCH STREQUAL "stm32f303x8")
    add_library(timer_stm32f303x8 STATIC timer_stm32f303x8.c)

    target_link_libraries(timer_stm32f303x8 
        INTERFACE timer
        PRIVATE stm32f303x8
    )
endif()