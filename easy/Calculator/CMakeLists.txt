cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(project "calculator")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
        calculator.cpp)

add_executable(${project} ${${project}_SOURCES})

add_subdirectory(expression_solver)
add_subdirectory(shunting_yard)
target_link_libraries(${project} expression_solver shunting_yard)

