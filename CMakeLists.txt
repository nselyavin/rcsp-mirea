cmake_minimum_required(VERSION 3.0.0)

set(this task_1)
project(${this} VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

find_package(rxcpp CONFIG)

if(rxcpp_FOUND)
    add_executable(${this} main.cpp)
    target_link_libraries(${this} PRIVATE rxcpp)
endif()

