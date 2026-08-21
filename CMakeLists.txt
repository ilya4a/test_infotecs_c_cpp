cmake_minimum_required(VERSION 3.16)
project(c_cpp_assignment)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(journal SHARED
        lib/src/FileJournal.cpp
        lib/src/Message.cpp
)

target_include_directories(journal PUBLIC
        lib/include
        app/include
)

add_executable(c_cpp_assignment app/src/main.cpp
        app/src/App.cpp
        app/include/App.h
        app/src/ThreadSafeQueue.cpp
        app/include/ThreadSafeQueue.h
        lib/include/Message.h
        app/include/Command.cpp
        app/include/Command.h)
target_link_libraries(c_cpp_assignment PRIVATE journal)