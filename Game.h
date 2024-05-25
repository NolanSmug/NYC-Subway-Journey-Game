//
// Created by Nolan Cyr on 5/5/24.
//

#ifndef NYC_SUBWAY_JOURNEY_GAME_GAME_H
#define NYC_SUBWAY_JOURNEY_GAME_GAME_H

#include "Station.h"
#include "SubwayMap.h"
#include "Line.h"
#include "Challenge.h"
#include "Train.h"
#include "GameState.h"
#include "GameStats.h"
#include "UserInterface.h"
#include "UserPrompt.h"
#include <iostream>
#include "sstream"
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <cstdlib>
#include <unordered_map>

// Game.h
class Game {
public:
    void runGame(int argc, char* argv[]);

private:
    /********************** Initialize the Game *********************/
    void initializeTrain(Train &train, GameState &gameState);
    void resetGame(GameState &gameState);

    /********************** Handling User Actions *********************/
    bool handleUserInput(Train &train, GameState& gameState);

    /******************* Performing Train Actions ********************/
    bool advanceToNextStation(Train &train, GameState &gameState);
    bool changeDirection(Train& train);
    bool advanceMultipleStations(Train &train, GameState &gameState, string &input);
    bool initializeTransfer(Train &train, GameState &gameState);

    void initializeArgs(int argc, char* argv[]);

    UserInterface ui;
    UserPrompt prompt;
};



#endif //NYC_SUBWAY_JOURNEY_GAME_GAME_H
