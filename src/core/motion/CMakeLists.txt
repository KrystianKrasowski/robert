add_library(motion STATIC motion.h motion_l293.c)

target_include_directories(motion
    PUBLIC
        "./"
)

target_link_libraries(motion
    PUBLIC gpio
    PRIVATE pwm
)