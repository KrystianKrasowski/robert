cmake_minimum_required(VERSION 3.27)

set(MCU atmega88pa)

project(robert VERSION 2.2.0 LANGUAGES C)

include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)

option(ROBERT_ENABLE_TESTS OFF)

add_subdirectory(test)
add_subdirectory(app)
add_subdirectory(src)