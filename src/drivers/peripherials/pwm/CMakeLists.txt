add_library(pwm INTERFACE pwm.h)

target_include_directories(pwm
    INTERFACE
        "./"
)

add_library(pwm_atmega88pa STATIC pwm_atmega88pa.c)

target_link_libraries(pwm_atmega88pa
    INTERFACE
        pwm
)