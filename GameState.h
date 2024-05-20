//
// Created by Nolan Cyr on 5/18/24.
//

#ifndef NYC_SUBWAY_JOURNEY_GAME_GAMESTATE_H
#define NYC_SUBWAY_JOURNEY_GAME_GAMESTATE_H

#include "Line.h"
#include "Station.h"
#include "SubwayMap.h"

class GameState {
public:
    LineName startingLine;
    Station startingStation;
    Station destinationStation;
    Station currentStation;
    vector<Station> currentStations;
    bool isFirstTurn;

    void resetGameState();
};


#endif //NYC_SUBWAY_JOURNEY_GAME_GAMESTATE_H
