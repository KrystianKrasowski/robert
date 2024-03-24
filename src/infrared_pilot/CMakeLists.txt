add_library(infrared_pilot STATIC infrared_pilot.c infrared_pilot.h)
target_include_directories(infrared_pilot PUBLIC "./")
target_link_libraries(infrared_pilot PUBLIC avrhal)