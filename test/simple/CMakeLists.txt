set(TEST_NAME simple)
add_executable(${TEST_NAME} simple.c)

target_link_libraries(${TEST_NAME} PRIVATE unity)
target_include_directories(${TEST_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/test/include)

add_test(${TEST_NAME} ${TEST_NAME})