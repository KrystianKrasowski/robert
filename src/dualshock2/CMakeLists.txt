add_library(dualshock2 STATIC dualshock2.c dualshock2.h)
target_include_directories(dualshock2 PUBLIC "./")
target_link_libraries(dualshock2 PUBLIC avrhal)