//
// Created by Nolan Cyr on 5/18/24.
//

#ifndef NYC_SUBWAY_JOURNEY_GAME_GAMESTATE_H
#define NYC_SUBWAY_JOURNEY_GAME_GAMESTATE_H

#include "../../Core/Line/Line.h"
#include "../Core/Station/Station.h"
#include "../../Core/SubwayMap/SubwayMap.h"
#include "../../Core/GameStats/GameStats.h"

class GameState {
public:
    LineName startingLine;
    Station startingStation;
    Station destinationStation;
    Station currentStation;
    vector<Station> currentStations;
    bool isFirstTurn;

    GameStats gameStats;

    static bool challengeModeFlag; // -c in args to set to false
    static bool easyModeFlag;     // -e in args to set to true

    void resetGameState();
};


#endif //NYC_SUBWAY_JOURNEY_GAME_GAMESTATE_H
