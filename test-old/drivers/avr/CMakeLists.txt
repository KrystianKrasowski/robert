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


set(DUALSHOCK2_TEST dualshock2_test)
add_executable(${DUALSHOCK2_TEST} ${DUALSHOCK2_TEST}.c)

target_include_directories(${DUALSHOCK2_TEST} PRIVATE 
    ${PROJECT_SOURCE_DIR}/test/include
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${DUALSHOCK2_TEST} PRIVATE 
    dualshock2
    unity
)

add_test(${TEST_NAME} ${TEST_NAME})
add_test(${DUALSHOCK2_TEST} ${DUALSHOCK2_TEST})