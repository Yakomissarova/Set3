cmake_minimum_required(VERSION 4.1)
project(A2_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp
        array_generator.cpp
        tester.cpp
        algorithms.cpp)
add_executable(set3_A2 set3_A2.cpp)
