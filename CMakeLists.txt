cmake_minimum_required(VERSION 3.16)

project(c_cpp_assignment LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(journal SHARED
        lib/src/FileJournal.cpp
        lib/src/Message.cpp
)

target_include_directories(journal
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/include
)


add_executable(app
        app/src/main.cpp
        app/src/App.cpp
        app/src/ThreadSafeQueue.cpp
        app/src/Command.cpp
)

target_include_directories(app
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/app/include
)

target_link_libraries(app
        PRIVATE
        journal
)


add_executable(tests
        tests/main.cpp
        tests/TestThreadSafeQueue.cpp
        tests/TestFileJournal.cpp
        tests/TestApp.cpp

        app/src/App.cpp
        app/src/ThreadSafeQueue.cpp
        app/src/Command.cpp
)

target_include_directories(tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/app/include
)

target_link_libraries(tests
        PRIVATE
        journal
)