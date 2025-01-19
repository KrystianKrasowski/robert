target_link_libraries(pwm_atmega88pa 
    PUBLIC
        atmega88pa-stub
)

add_executable(pwm_atmega88pa_test pwm_atmega88pa_test.c)

target_include_directories(pwm_atmega88pa_test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/test/include
)

target_link_libraries(pwm_atmega88pa_test
    INTERFACE
        pwm
    PRIVATE
        pwm_atmega88pa
        unity
)

add_test(pwm_atmega88pa_test pwm_atmega88pa_test)