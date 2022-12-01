cmake_minimum_required(VERSION 3.0.0)

set(this task_3)
project(${this} VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 20)

find_package(rxcpp CONFIG)


add_executable(${this} main.cpp File.h Generator.h Handler.h)

