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

set_target_properties( client
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)



set_property(TARGET client PROPERTY
    CXX_STANDARD 17
)

target_include_directories(client
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/src/
)

target_link_libraries( client
    PRIVATE 
        logger socket command_line_args_parser
)
