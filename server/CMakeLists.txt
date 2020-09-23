cmake_minimum_required(VERSION 3.5)

project(server)

set(SOURCES
    main.cpp
    server.cpp
)

set(HEADERS
    server.hpp
)

add_executable(server ${SOURCES} ${HEADERS})

set_property(TARGET server PROPERTY
    CXX_STANDARD 17
)

target_include_directories(server
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/socket_lib/
        ${CMAKE_SOURCE_DIR}/logger/
        ${CMAKE_SOURCE_DIR}/command_line_args_parser/
)

target_link_libraries( server
    PRIVATE 
        logger socket_lib command_line_args_parser
)
