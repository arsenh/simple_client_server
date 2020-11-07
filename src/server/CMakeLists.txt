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

if (UNIX)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(server PRIVATE Threads::Threads)
endif (UNIX)

set_target_properties( server
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

set_property(TARGET server PROPERTY
    CXX_STANDARD 17
)

target_include_directories(server
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries( server
    PRIVATE 
        logger socket command_line_args_parser
)
