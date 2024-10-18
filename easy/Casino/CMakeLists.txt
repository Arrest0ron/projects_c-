cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(project "casino")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
        casino.cpp)

add_executable(${project} ${${project}_SOURCES})

add_subdirectory(slot)
add_subdirectory(roulette)
target_link_libraries(${project} slot roulette)

