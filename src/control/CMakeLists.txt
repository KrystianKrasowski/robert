add_library(control STATIC control.c)
target_include_directories(control PRIVATE
    ${PROJECT_SOURCE_DIR}/include/control
    ${PROJECT_SOURCE_DIR}/include/dualshock2
)