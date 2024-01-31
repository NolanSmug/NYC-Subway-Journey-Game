cmake_minimum_required(VERSION 3.26)
project(M1OEP_ncyr1)

set(CMAKE_CXX_STANDARD 17)

add_executable(M1OEP_ncyr1 main.cpp Train.cpp Train.h
        Station.h
        Station.cpp)
