cmake_minimum_required(VERSION 4.1)
project(A3b)

set(CMAKE_CXX_STANDARD 17)

add_executable(A3b main.cpp
        array_generator.cpp
        tester.cpp
        algorithms.cpp)
add_executable(set3_A3b set3_A3b.cpp)
