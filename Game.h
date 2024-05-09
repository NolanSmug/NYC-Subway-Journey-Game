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
#include <iostream>
#include "sstream"
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <cstdlib>
#include <unordered_map>

/// basically is the reason the game works
struct GameState {
    LineName startingLine;
    Station startingStation;
    Station destinationStation;
    Station currentStation;
    vector<Station> currentStations;
    bool isFirstTurn;

    void resetGameState();
};

using namespace std;

class Game {
public:
    void startGame(int argc, char* argv[]);

private:
/********************** Initialize the Game *********************/
    void initializeTrain(Train &train, GameState &gameState);

/******************** Prompting for Game Setup ********************/
    void promptForGameMode(GameState &gameState);

/**************** Prompting for Challenge Setup *******************/
    void promptForChallengeSelection(GameState &gameState);
    void promptsForCustomChallenge(Challenge &challenge);
    LineName promptLineSelection(bool isStartingStation);
    Station promptStationFromLine(LineName line, bool isStartingStation);

/******************* Prompting for Train Actions ********************/
    void promptForStartingLine(Train &train);
    void promptForDirection(Train &train);
    void promptForAtRockawayBranch(Train &train, GameState &gameState);
    bool handleUserInput(Train &train, GameState &gameState);

/******************* Performing Train Actions ********************/
    bool advanceToNextStation(Train &train);
    bool changeDirection(Train &train);
    bool advanceMultipleStations(Train &train, string &input);
    bool initializeTransfer(Train &train);
    bool promptForTransfer(Train &train);

/**************** Displaying Game Information *******************/
    void displayCurrentLineInfo(Train &train);
    void displayCurrentStationInfo(Train &train);
    void announceLastStop(Train &train);
    void displayUpcomingStations(Train &train);
    void displayAllChallenges(Challenge challenge);
    void displayStationsFor(vector<Station> stations);

    static bool isnumber(const string &s);
    void initializeArgs(int argc, char *argv[]);
};


#endif //NYC_SUBWAY_JOURNEY_GAME_GAME_H
