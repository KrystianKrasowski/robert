set(TEST_NAME motion_l293_test)
add_executable(${TEST_NAME} motion_l293.c)

target_include_directories(${TEST_NAME} PUBLIC 
    ${PROJECT_SOURCE_DIR}/test/include
    ${PROJECT_SOURCE_DIR}/include/motion
)

target_link_libraries(${TEST_NAME} PUBLIC 
    motion
    l293
    unity
    atmega88pa-hal
)

add_test(${TEST_NAME} ${TEST_NAME})