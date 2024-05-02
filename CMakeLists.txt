cmake_minimum_required(VERSION 3.27)

set(MCU atmega88pa)

project(robert VERSION 2.2.0 LANGUAGES C)

include(FetchContent)

FetchContent_Declare(
    atmega88pa-hal
    GIT_REPOSITORY https://github.com/KrystianKrasowski/atmega88pa-hal.git
    GIT_TAG feature/interface-separation
)

FetchContent_MakeAvailable(atmega88pa-hal)

add_subdirectory(app)
add_subdirectory(src)