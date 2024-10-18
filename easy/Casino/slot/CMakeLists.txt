cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(project "slot")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
        slot.cpp)

set(${project}_HEADERS
        slot.hpp)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

add_library(${project}
        STATIC
        ${${project}_SOURCE_LIST})
