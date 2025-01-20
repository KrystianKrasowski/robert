add_library("command" STATIC "command.h" command_dualshock2.c)

target_include_directories("command"
    PUBLIC
        "./"
)

target_link_libraries("command"
    PRIVATE
        dualshock2
)

add_library(command_stub STATIC "command.h" command_stub.c)

target_include_directories(command_stub
    PUBLIC
        "./"
)