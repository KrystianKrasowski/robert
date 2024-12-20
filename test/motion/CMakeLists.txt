set(TEST_NAME motion_l293_test)
add_executable(${TEST_NAME} motion_l293.c)

target_link_libraries(l293 PUBLIC atmega88pa-stub)
target_link_libraries(${TEST_NAME} PUBLIC motion unity)
target_include_directories(${TEST_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/test/include)

add_test(${TEST_NAME} ${TEST_NAME})