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
    GameStats(int totalStationsVisited, int totalTransfers, vector<LineName> linesVisited, vector<Borough> boroughsVisited);

    void incrementStationsVisited();
    void incrementTransfers();

    int getTotalStationsVisited();
    int getTotalTransfers();

    vector<LineName> getLinesVisited();
    vector<Borough> getBoroughsVisited();

    void addToLinesVisited(LineName lineName);
    void addToBoroughsVisited(Borough borough);

    void resetStats();

private:
    int totalStationsVisited;
    int totalTransfers;

    vector<LineName> linesVisited;
    vector<Borough> boroughsVisited;
};

#endif //NYC_SUBWAY_JOURNEY_GAME_GAMESTATS_H
