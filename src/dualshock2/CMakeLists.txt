add_library(dualshock2 STATIC dualshock2.c)
target_include_directories(dualshock2 PRIVATE ${PROJECT_SOURCE_DIR}/include/dualshock2)
target_link_libraries(dualshock2 PRIVATE avrhal)