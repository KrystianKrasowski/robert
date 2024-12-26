add_library(l293 STATIC l293.c)
target_include_directories(l293 PRIVATE ${PROJECT_SOURCE_DIR}/include/l293)
target_link_libraries(l293 PRIVATE avrhal)