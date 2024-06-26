//
// Created by Nolan Cyr on 2/1/24.
//
#ifndef NYC_SUBWAY_JOURNEY_GAME_SUBWAYMAP_H
#define NYC_SUBWAY_JOURNEY_GAME_SUBWAYMAP_H

#include <string>
#include <vector>
#include "../Line/Line.h"

class Station;

using namespace std;

class SubwayMap {
public:
    static void createStations(LineName line, vector<Station> &subwayStations);

    static void updateStopsForLine(LineName line, vector<Station> &subwayStations);
};
#endif //NYC_SUBWAY_JOURNEY_GAME_SUBWAYMAP_H
