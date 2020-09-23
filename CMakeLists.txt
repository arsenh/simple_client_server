cmake_minimum_required (VERSION 3.5)

project(simple_client_server)

# Add sub directories
add_subdirectory(logger)
add_subdirectory(socket_lib)
add_subdirectory(command_line_args_parser)
add_subdirectory(client)
add_subdirectory(server)
