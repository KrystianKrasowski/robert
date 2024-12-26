add_library(motion STATIC motion_l293.c)
target_include_directories(motion PRIVATE
    ${PROJECT_SOURCE_DIR}/include/motion
    ${PROJECT_SOURCE_DIR}/include/l293
)
target_link_libraries(motion PRIVATE avrhal)