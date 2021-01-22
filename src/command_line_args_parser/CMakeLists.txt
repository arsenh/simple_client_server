cmake_minimum_required(VERSION 3.5)

project(command_line_args_parser)

set(SOURCES
    command_line_args_parser.cpp
)

set(HEADERS
    command_line_args_parser.hpp
)

add_library(command_line_args_parser STATIC ${SOURCES} ${HEADERS})

set_target_properties( command_line_args_parser
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

set_property(TARGET command_line_args_parser PROPERTY
    CXX_STANDARD 17
)

target_link_libraries( command_line_args_parser
    PRIVATE
        logger
)

