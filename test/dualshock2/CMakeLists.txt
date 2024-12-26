set(TEST_NAME dualshock2_test)
add_executable(${TEST_NAME} dualshock2.c)

target_include_directories(${TEST_NAME} PUBLIC 
    ${PROJECT_SOURCE_DIR}/test/include
    ${PROJECT_SOURCE_DIR}/include/dualshock2
)

target_link_libraries(${TEST_NAME} PUBLIC 
    dualshock2 
    unity
    atmega88pa-hal
)

add_test(${TEST_NAME} ${TEST_NAME})