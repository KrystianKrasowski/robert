cmake_minimum_required(VERSION 3.27)

set(MCU atmega88pa)

project(robert VERSION 2.2.0 LANGUAGES C)

include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)

add_subdirectory(app)
add_subdirectory(src)

if(${ENABLE_TESTS})
    target_compile_definitions(avrhal INTERFACE __AVR_ATmega88PA__)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif()