target_link_libraries(timer_atmega88pa 
    PUBLIC
        atmega88pa-stub
)

add_executable(timer_atmega88pa_test timer_atmega88pa_test.c)

target_include_directories(timer_atmega88pa_test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/test/include
)

target_link_libraries(timer_atmega88pa_test
    INTERFACE
        timer
    PRIVATE
        timer_atmega88pa
        unity
)

add_test(timer_atmega88pa_test timer_atmega88pa_test)