cmake_minimum_required(VERSION 3.26)
project(M2OEP_ncyr1)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp Line.cpp Station.cpp SubwayMap.cpp Train.cpp)

add_executable(tests testing.cpp Line.cpp Station.cpp SubwayMap.cpp Train.cpp)
