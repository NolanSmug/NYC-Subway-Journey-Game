//
// Created by Nolan Cyr on 5/5/24.
//

#ifndef NYC_SUBWAY_JOURNEY_GAME_GAME_H
#define NYC_SUBWAY_JOURNEY_GAME_GAME_H

#include "../Station/Station.h"
#include "../SubwayMap/SubwayMap.h"
#include "../Line/Line.h"
#include "../../Game/Challenge/Challenge.h"
#include "../Train/Train.h"
#include "../../Game/GameState/GameState.h"
#include "../GameStats/GameStats.h"
#include "../../UI/UserInterface/UserInterface.h"
#include "../../UI/UserPrompt/UserPrompt.h"
#include <iostream>
#include "sstream"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <unordered_map>

// Game.h
class Game {
public:
    void runGame();
    void initializeArgs(int argc, char* argv[]);

private:
    /********************** Initialize the Game *********************/
    void initializeTrain(Train &train, GameState &gameState);
    void resetGame(GameState &gameState);

    /********************** Handling User Actions *********************/
    void handleUserInput(Train &train, GameState& gameState);

    /******************* Performing Train Actions ********************/
    bool advanceToNextStation(Train &train, GameState &gameState);
    bool advanceMultipleStations(Train &train, GameState &gameState, string &input);
    bool initializeTransfer(Train &train, GameState &gameState);

    UserInterface ui;
    UserPrompt prompt;
};


#endif //NYC_SUBWAY_JOURNEY_GAME_GAME_H
