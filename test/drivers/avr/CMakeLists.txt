set(TEST_NAME motion_l293_test)
add_executable(${TEST_NAME} ${TEST_NAME}.c)

target_include_directories(${TEST_NAME} PRIVATE 
    ${PROJECT_SOURCE_DIR}/test/include
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${TEST_NAME} PRIVATE 
    motion
    unity
)

add_test(${TEST_NAME} ${TEST_NAME})