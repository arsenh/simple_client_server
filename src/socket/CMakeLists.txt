cmake_minimum_required(VERSION 3.5)

project(socket)

set(SOURCES
    tcpSocket.cpp
)

set(HEADERS
    tcpSocket.hpp
)

add_library(socket STATIC ${SOURCES} ${HEADERS})

set_target_properties( socket
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

set_property(TARGET socket PROPERTY
    CXX_STANDARD 17
)

target_link_libraries( socket
    PRIVATE
        logger
)

