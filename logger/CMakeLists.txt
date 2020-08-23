cmake_minimum_required(VERSION 3.5)

project(logger)

set(SOURCES
    logger.cpp
)

set(HEADERS
    logger.hpp
)

add_library(logger STATIC ${SOURCES} ${HEADERS})

set_property(TARGET logger PROPERTY
    CXX_STANDARD 17
)

