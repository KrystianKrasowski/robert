add_library(timer INTERFACE timer.h)

target_include_directories(timer
    INTERFACE
        "./"
)

add_library(timer_atmega88pa STATIC timer_atmega88pa.c)

target_link_libraries(timer_atmega88pa
    INTERFACE
        timer
)