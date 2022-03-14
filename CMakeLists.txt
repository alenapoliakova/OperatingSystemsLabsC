cmake_minimum_required(VERSION 3.21)
project(operation_systems)

set(CMAKE_CXX_STANDARD 14)

include_directories(1_scheduler_two_process)

add_executable(operation_systems
        1_scheduler_two_process/scheduler.cpp)
