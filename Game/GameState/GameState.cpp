//
// Created by Nolan Cyr on 5/18/24.
//

#include "GameState.h"


bool GameState::challengeModeFlag = true; // -c in args to set to false
bool GameState::easyModeFlag = false;     // -e in args to set to true

void GameState::resetGameState() { // if user wants to re-shuffle their stations
    startingLine = Line::getRandomLine();
    isFirstTurn = true;
    gameStats.resetStats(); // reset stats

    SubwayMap::createStations(startingLine, currentStations); // fill currentStations vector for currentLine

    Station station;

    startingStation = station.getRandomStation(currentStations);
    do {
        destinationStation = Station::getRandomStation(Station::allNycStations); // select random destination station
    } while (startingStation == destinationStation); // ensure starting != destination

    currentStation = startingStation; // update current station too

}
