cmake_minimum_required(VERSION 3.27)

set(MCU atmega88pa)

project(robert VERSION 2.1.1 LANGUAGES C)

include(FetchContent)

FetchContent_Declare(
    avrhal
    GIT_REPOSITORY https://github.com/KrystianKrasowski/atmega88pa-hal.git
    GIT_TAG feature/timer1-pwm
)

FetchContent_MakeAvailable(avrhal)

add_subdirectory(app)
add_subdirectory(src)