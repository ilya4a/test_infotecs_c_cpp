cmake_minimum_required(VERSION 4.1)
project(c_cpp_assignment)

set(CMAKE_CXX_STANDARD 20)

add_executable(c_cpp_assignment main.cpp
        include/IJournal.h
        include/LogLevel.h)
