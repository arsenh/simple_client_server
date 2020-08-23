cmake_minimum_required(VERSION 3.5)

project(socket_lib)

set(SOURCES
    socket.cpp
)

set(HEADERS
    socket.hpp
)

add_library(socket_lib STATIC ${SOURCES} ${HEADERS})

set_property(TARGET socket_lib PROPERTY
    CXX_STANDARD 17
)

target_link_libraries( socket_lib
    PRIVATE
        logger
)

