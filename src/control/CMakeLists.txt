add_library(control STATIC control_dualshock2.c control.h)
target_include_directories(control PUBLIC "./")
target_link_libraries(control PUBLIC dualshock2)