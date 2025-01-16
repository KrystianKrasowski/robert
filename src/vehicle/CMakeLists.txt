add_library(vehicle STATIC vehicle.c)

target_include_directories(vehicle PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)