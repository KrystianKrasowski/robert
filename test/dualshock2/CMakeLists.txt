set(TEST_NAME dualshock2_test)
add_executable(${TEST_NAME} dualshock2.c)

target_link_libraries(dualshock2 PUBLIC atmega88pa-stub)
target_link_libraries(${TEST_NAME} PUBLIC atmega88pa-stub dualshock2 unity)
target_include_directories(${TEST_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/test/include)

add_test(${TEST_NAME} ${TEST_NAME})