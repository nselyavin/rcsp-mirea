cmake_minimum_required(VERSION 3.0.0)

set(this task_4)
project(${this} VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 20)

find_package(rxcpp CONFIG)

if(rxcpp_FOUND)
    add_executable(${this} main.cpp File.h Generator.h Handler.h)
    target_link_libraries(${this} PRIVATE rxcpp)
else()
    message(FATAL_ERROR "rxcpp not found")
endif()

