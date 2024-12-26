include(FetchContent)

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG v2.6.0
)

FetchContent_Declare(
    atmega88pa-hal
    GIT_REPOSITORY https://github.com/KrystianKrasowski/atmega88pa-hal.git
    GIT_TAG 3.2.0
)

FetchContent_MakeAvailable(unity)
FetchContent_MakeAvailable(atmega88pa-hal)