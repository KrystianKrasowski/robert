add_library(pwm INTERFACE pwm.h)

target_include_directories(pwm
    INTERFACE
        "./"
)

if(TARGET_ARCH STREQUAL "atmega88pa" OR TARGET_ARCH STREQUAL "test")
    add_library(pwm_atmega88pa STATIC pwm_atmega88pa.c)
    target_link_libraries(pwm_atmega88pa INTERFACE pwm)
endif()

if(TARGET_ARCH STREQUAL "stm32f303x8")
    add_library(pwm_stm32f303x8 STATIC pwm_stm32f303x8.c)

    target_link_libraries(pwm_stm32f303x8 
        INTERFACE pwm
        PRIVATE stm32f303x8
    )
endif()