cmake_minimum_required(VERSION 3.27)

set(MCU atmega88pa)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/avr-gcc.cmake")

project(robert VERSION 1.0.0 LANGUAGES C)

include(FetchContent)

FetchContent_Declare(
    avrhal
    GIT_REPOSITORY https://github.com/KrystianKrasowski/atmega88pa-hal.git
    GIT_TAG feature/cmake
)

FetchContent_MakeAvailable(avrhal)

add_subdirectory(app)
add_subdirectory(src)