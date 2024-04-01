add_library(l293 STATIC l293.c l293.h)
target_include_directories(l293 PUBLIC "./")
target_link_libraries(l293 PUBLIC avrhal)