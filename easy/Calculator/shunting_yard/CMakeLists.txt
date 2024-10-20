cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(project "shunting_yard")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
        shunting_yard.cpp
        shunting_yard.hpp)


add_library(${project} STATIC ${${project}_SOURCES})
