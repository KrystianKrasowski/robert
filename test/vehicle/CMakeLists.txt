add_library(vehicle_command_mock STATIC vehicle_command_mock.c)
target_include_directories(vehicle_command_mock PRIVATE
    ${PROJECT_SOURCE_DIR}/include/vehicle
    ${PROJECT_SOURCE_DIR}/test/include/vehicle
)

add_library(vehicle_motion_mock STATIC vehicle_motion_mock.c)
target_include_directories(vehicle_motion_mock PRIVATE
    ${PROJECT_SOURCE_DIR}/include/vehicle
    ${PROJECT_SOURCE_DIR}/test/include/vehicle
)


set(TEST_NAME vehicle_test)
add_executable(${TEST_NAME} vehicle_test.c)

target_include_directories(${TEST_NAME} PRIVATE 
    ${PROJECT_SOURCE_DIR}/include/vehicle
    ${PROJECT_SOURCE_DIR}/test/include
    ${PROJECT_SOURCE_DIR}/test/include/vehicle
)

target_link_libraries(${TEST_NAME} PRIVATE 
    vehicle 
    vehicle_command_mock 
    vehicle_motion_mock 
    unity
)

add_test(${TEST_NAME} ${TEST_NAME})