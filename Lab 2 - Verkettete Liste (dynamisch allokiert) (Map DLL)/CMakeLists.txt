cmake_minimum_required(VERSION 4.1)
project(TemaLabDSA2)

set(CMAKE_CXX_STANDARD 20)

add_executable(TemaLabDSA2
        Map.h
        MapIterator.h
        MapIterator.cpp
        Map.cpp
        ShortTest.cpp
        App.cpp
        ExtendedTest.cpp)
