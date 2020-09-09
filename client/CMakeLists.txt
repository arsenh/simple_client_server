cmake_minimum_required(VERSION 3.5)

project(client)

set(SOURCES
    main.cpp
    client.cpp
)

set(HEADERS
    client.hpp
)

add_executable(client ${SOURCES} ${HEADERS})

set_property(TARGET client PROPERTY
    CXX_STANDARD 17
)

target_include_directories(client
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/socket_lib/
        ${CMAKE_SOURCE_DIR}/logger/
)

target_link_libraries( client
    PRIVATE 
        logger socket_lib
)
