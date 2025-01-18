target_link_libraries(motion PUBLIC atmega88pa-stub)
target_link_libraries(dualshock2 PUBLIC atmega88pa-stub)

add_subdirectory(atmega88pa-stub)
add_subdirectory(vehicle)
add_subdirectory(drivers/avr)