set(TEST_NAME vehicle_motion_l293_test)
add_executable(${TEST_NAME} ${TEST_NAME}.c)

target_include_directories(${TEST_NAME} PUBLIC 
    ${PROJECT_SOURCE_DIR}/test/include
    ${PROJECT_SOURCE_DIR}/include/vehicle
)

target_link_libraries(${TEST_NAME} PUBLIC 
    vehicle_motion_l293
    unity
)

add_test(${TEST_NAME} ${TEST_NAME})