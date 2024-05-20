//
// Created by Nolan Cyr on 5/18/24.
//

#include "GameState.h"

void GameState::resetGameState() { // if user wants to re-shuffle their stations
    startingLine = Line::getRandomLine();
    isFirstTurn = true;

    SubwayMap::createStations(startingLine, currentStations); // fill currentStations vector for currentLine

    startingStation = Station::getRandomStation(currentStations);
    do {
        destinationStation = Station::getRandomStation(Station::allNycStations); // select random destination station
    } while (startingStation == destinationStation); // ensure starting != destination

    currentStation = startingStation; // update current station too
}
