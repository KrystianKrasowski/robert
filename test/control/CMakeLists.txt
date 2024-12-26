set(TEST_NAME control_test)
add_executable(${TEST_NAME} control.c)

target_include_directories(${TEST_NAME} PUBLIC 
    ${PROJECT_SOURCE_DIR}/test/include
    ${PROJECT_SOURCE_DIR}/include/control
    ${PROJECT_SOURCE_DIR}/include/dualshock2
)

target_link_libraries(${TEST_NAME} PUBLIC control unity)

add_test(${TEST_NAME} ${TEST_NAME})