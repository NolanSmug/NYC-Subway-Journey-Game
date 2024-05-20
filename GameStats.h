//
// Created by Nolan Cyr on 5/16/24.
//

#ifndef NYC_SUBWAY_JOURNEY_GAME_GAMESTATS_H
#define NYC_SUBWAY_JOURNEY_GAME_GAMESTATS_H

#include <set>
#include "Station.h"

using namespace std;

class GameStats {
public:
    GameStats();
    GameStats(int totalStationsVisited, int totalTransfers, set<LineName> linesVisited, set<Borough> boroughsVisited);

    void incrementStationsVisited();
    void incrementTransfers();

    int getTotalStationsVisited();
    int getTotalTransfers();

    set<LineName> getLinesVisited();
    set<Borough> getBoroughsVisited();

    void addToLinesVisited(LineName lineName);
    void addToBoroughsVisited(Borough borough);

    void resetStats();

private:
    int totalStationsVisited;
    int totalTransfers;

    set<LineName> linesVisited;
    set<Borough> boroughsVisited;
};

#endif //NYC_SUBWAY_JOURNEY_GAME_GAMESTATS_H
