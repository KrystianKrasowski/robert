add_library(command STATIC command_dualshock2.c)
target_include_directories(command PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

add_library(motion STATIC motion_l293.c)
target_include_directories(motion PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(motion PUBLIC stm32f303x8)