add_library(motion STATIC motion_l293.c)
target_include_directories(motion PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

add_library(command STATIC command_dualshock2.c)
target_include_directories(command PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

add_library(dualshock2 STATIC dualshock2.c)
target_include_directories(dualshock2 PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)