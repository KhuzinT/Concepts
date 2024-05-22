cmake_minimum_required(VERSION 3.22)
project(vm)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp src/VirtualMachine.cpp)