cmake_minimum_required(VERSION 3.26)
project(NYC_Subway_Journey_Game)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        ${PROJECT_SOURCE_DIR}/Core/GameLogic
        ${PROJECT_SOURCE_DIR}/Core/Station
        ${PROJECT_SOURCE_DIR}/Core/Line
        ${PROJECT_SOURCE_DIR}/Core/Train
        ${PROJECT_SOURCE_DIR}/Core/GameStats
        ${PROJECT_SOURCE_DIR}/Core/SubwayMap

        ${PROJECT_SOURCE_DIR}/UI/UserInterface
        ${PROJECT_SOURCE_DIR}/UI/UserPrompt

        ${PROJECT_SOURCE_DIR}/Game/Challenge
        ${PROJECT_SOURCE_DIR}/Game/GameState

        ${PROJECT_SOURCE_DIR}/Main
)

set(SOURCES
        Core/GameLogic/Game.cpp
        Core/Station/Station.cpp
        Core/Line/Line.cpp
        Core/Train/Train.cpp
        Core/GameStats/GameStats.cpp
        Core/SubwayMap/SubwayMap.cpp

        UI/UserInterface/UserInterface.cpp
        UI/UserPrompt/UserPrompt.cpp

        Game/Challenge/Challenge.cpp
        Game/GameState/GameState.cpp

        Main/main.cpp
        UI/UserPrompt/UserPrompt.h
)

add_executable(NYC_Subway_Journey_Game ${SOURCES})
