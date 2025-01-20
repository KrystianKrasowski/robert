cmake_minimum_required(VERSION 3.27)

project(robert VERSION 4.0.0 LANGUAGES C)

include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)

set(TARGET_ARCH "test" CACHE STRING "Target architecture name")

include(CTest)
enable_testing()

# TODO: Introduce TARGET_ARCH flag for clearer logic in subdirectories

add_subdirectory(app)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)