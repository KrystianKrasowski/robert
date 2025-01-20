set(MAIN_EXECUTABLE ${PROJECT_NAME})

add_executable(${MAIN_EXECUTABLE} main.c)

target_include_directories(${MAIN_EXECUTABLE} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${MAIN_EXECUTABLE} PRIVATE 
    vehicle
    command
    motion
)

add_custom_command(TARGET ${MAIN_EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-size ${MAIN_EXECUTABLE}.elf
)

add_custom_command(TARGET ${MAIN_EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex ${MAIN_EXECUTABLE}.elf ${PROJECT_NAME}.hex
    COMMAND arm-none-eabi-objcopy -O binary ${MAIN_EXECUTABLE}.elf ${PROJECT_NAME}.bin
)

add_custom_target(flash
    COMMAND st-flash write ${PROJECT_NAME}.bin 0x08000000
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/app/arm
    COMMENT "Flashing ${PROJECT_NAME}.bin"
)