cmake_minimum_required(VERSION 3.5)

project(server)

set(SOURCES
    server.cpp
)

#set(HEADERS
#    socket.hpp
#)

add_executable(server ${SOURCES}) #${HEADERS})

set_property(TARGET server PROPERTY
    CXX_STANDARD 17
)

target_include_directories(server
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/socket_lib/
        ${CMAKE_SOURCE_DIR}/logger/
)

target_link_libraries( server
    PRIVATE 
        logger socket_lib
)
