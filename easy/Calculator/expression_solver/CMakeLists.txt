cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(project "expression_solver")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
        expression_solver.cpp
        expression_solver.hpp)


add_library(${project} STATIC ${${project}_SOURCES})
