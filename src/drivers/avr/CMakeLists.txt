add_library(vehicle_motion_l293 STATIC vehicle_motion_l293.c)
target_include_directories(vehicle_motion_l293 PRIVATE
    ${PROJECT_SOURCE_DIR}/include/vehicle
    ${PROJECT_SOURCE_DIR}/test/include
)