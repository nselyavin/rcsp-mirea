cmake_minimum_required(VERSION 3.0.0)

set(this task_1)
project(${this} VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 20)

find_package(OpenMP)

add_executable(${this} main.cpp)

if(OpenMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    target_link_libraries(${this} PRIVATE ${OpenMP_CXX_LIBRARIES})
    target_include_directories(${this} PRIVATE ${OpenMP_CXX_INCLUDE_DIRS})
endif()


