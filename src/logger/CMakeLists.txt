cmake_minimum_required(VERSION 3.5)

project(logger)

set(SOURCES
    logger.cpp
)

set(HEADERS
    logger.hpp
)

add_library(logger STATIC ${SOURCES} ${HEADERS})

set_target_properties( logger
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

set_property(TARGET logger PROPERTY
    CXX_STANDARD 17
)

