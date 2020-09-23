cmake_minimum_required(VERSION 3.5)

project(command_line_args_parser)

set(SOURCES
    command_line_args_parser.cpp
)

set(HEADERS
    command_line_args_parser.hpp
)

add_library(command_line_args_parser STATIC ${SOURCES} ${HEADERS})

set_property(TARGET command_line_args_parser PROPERTY
    CXX_STANDARD 17
)

target_link_libraries( command_line_args_parser
    PRIVATE
        logger
)

