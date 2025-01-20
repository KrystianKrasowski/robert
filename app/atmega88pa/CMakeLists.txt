add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        vehicle
        "command"
        motion
        dualshock2
        gpio_atmega88pa
        timer_atmega88pa
        pwm_atmega88pa
        spi_atmega88pa
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
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/app/atmega88pa
    COMMENT "Flashing ${PROJECT_NAME}.hex"
)

add_custom_target(size
    COMMAND ${CMAKE_COMMAND_SIZE} --format=avr --mcu=${MCU} ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/app/atmega88pa
)