cmake_minimum_required(VERSION 3.26)
project(M3OEP-ncyr1)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp Line.cpp Station.cpp SubwayMap.cpp Train.cpp
        Challenge.h
        Challenge.cpp)

add_executable(tests testing.cpp Line.cpp Station.cpp SubwayMap.cpp Train.cpp)
