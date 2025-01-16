add_library(vehicle_motion_l293 STATIC vehicle_motion_l293.c)
target_include_directories(vehicle_motion_l293 PRIVATE
    ${PROJECT_SOURCE_DIR}/include/vehicle
    ${PROJECT_SOURCE_DIR}/test/include
)

add_library(vehicle_command_dualshock2 STATIC vehicle_command_dualshock2.c)
target_include_directories(vehicle_command_dualshock2 PRIVATE
    ${PROJECT_SOURCE_DIR}/include/vehicle
)
