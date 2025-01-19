add_library(vehicle STATIC vehicle.h vehicle.c)

target_include_directories(vehicle
    PUBLIC
        "./"
)

target_link_libraries(vehicle
    PRIVATE
        "command"
        motion
)