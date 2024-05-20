cmake_minimum_required(VERSION 3.26)
project(NYC-Subway-Journey-Game)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp Line.cpp Station.cpp SubwayMap.cpp Train.cpp
        Challenge.h
        Challenge.cpp
        Game.h
        Game.cpp
        GameStats.h
        GameStats.cpp
        GameState.h
        GameState.cpp
        UserInterface.h
        UserInterface.cpp
        UserPrompt.h
        UserPrompt.cpp

)
