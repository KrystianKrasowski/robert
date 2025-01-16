add_library(command_mock STATIC command_mock.c)
target_include_directories(command_mock PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

add_library(motion_mock STATIC motion_mock.c)
target_include_directories(motion_mock PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/test/include
)


set(TEST_NAME vehicle_test)
add_executable(${TEST_NAME} vehicle_test.c)

target_include_directories(${TEST_NAME} PRIVATE 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/test/include
)

target_link_libraries(${TEST_NAME} PUBLIC
    command_mock 
    motion_mock
    vehicle
    unity
)

add_test(${TEST_NAME} ${TEST_NAME})