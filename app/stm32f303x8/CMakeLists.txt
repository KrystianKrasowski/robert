add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        vehicle
        command_stub
        motion
        gpio_stm32f303x8
        timer_stm32f303x8
        pwm_stm32f303x8
)

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND arm-none-eabi-size ${PROJECT_NAME}.elf
)

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMAND arm-none-eabi-objcopy -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
)

add_custom_target(flash
    COMMAND st-flash write ${PROJECT_NAME}.bin 0x08000000
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/app/stm32f303x8
    COMMENT "Flashing ${PROJECT_NAME}.bin"
)