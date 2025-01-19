add_library("command" STATIC "command.h" command_dualshock2.c)

target_include_directories("command"
    PUBLIC
        "./"
)

target_link_libraries("command"
    PRIVATE
        dualshock2
)