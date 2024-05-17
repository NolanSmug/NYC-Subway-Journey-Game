//
// Created by Nolan Cyr on 5/16/24.
//

#ifndef NYC_SUBWAY_JOURNEY_GAME_GAMESTATS_H
#define NYC_SUBWAY_JOURNEY_GAME_GAMESTATS_H

#include <unordered_set>
#include "Station.h"

using namespace std;

class GameStats {
public:
    GameStats();

    void incrementStationsVisited();
    void incrementTransfers();

    int getTotalStationsVisited();
    int getTotalTransfers();

    void resetStats();

private:
    int totalStationsVisited;
    int totalTransfers;

};

#endif //NYC_SUBWAY_JOURNEY_GAME_GAMESTATS_H
