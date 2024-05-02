add_library(motion STATIC motion_l293.c motion.h)
target_include_directories(motion PUBLIC "./")
target_link_libraries(motion PUBLIC l293 atmega88pa-hal)