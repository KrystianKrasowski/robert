add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} PUBLIC
    control
    dualshock2
    infrared_pilot
    l293
    motion
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.hex
    COMMENT "Creating the hex file for ${PROJECT_NAME}"
)

add_custom_target(create_hex_file ALL DEPENDS ${PROJECT_NAME})

add_custom_target(flash
    COMMAND avrdude -c usbasp -p m88p -U flash:w:${PROJECT_NAME}.hex
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/app
    COMMENT "Flashing ${PROJECT_NAME}.hex"
)

add_custom_target(size
    COMMAND ${CMAKE_COMMAND_SIZE} --format=avr --mcu=${MCU} ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/app
)