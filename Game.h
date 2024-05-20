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
    void startGame(int argc, char* argv[]);

    static bool challengeModeFlag; // -c in args to set to false
    static bool easyModeFlag;     // -e in args to set to true
private:
    /********************** Initialize the Game *********************/
    void initializeTrain(Train &train, GameState &gameState);
    void resetGame(GameState &gameState);
    void updateTrainState(Train &train, bool &isAtATrainJunction, bool &atLastStop);

    /********************** Handling User Actions *********************/
    bool handleUserInput(Train &train, GameState& gameState);

    /******************* Performing Train Actions ********************/
    bool advanceToNextStation(Train& train);
    bool changeDirection(Train& train);
    bool advanceMultipleStations(Train& train, string& input);
    bool initializeTransfer(Train& train);

    void initializeArgs(int argc, char* argv[]);
};



#endif //NYC_SUBWAY_JOURNEY_GAME_GAME_H
