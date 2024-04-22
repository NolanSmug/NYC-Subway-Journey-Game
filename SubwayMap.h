//
// Created by Nolan Cyr on 2/1/24.
//
#ifndef M1OEP_NCYR1_SUBWAYMAP_H
#define M1OEP_NCYR1_SUBWAYMAP_H

#include <string>
#include <vector>
#include "Station.h"
#include "SubwayMap.h"

class SubwayMap {
public:
    static void createStations(LineName line, vector<Station> &subwayStations);

    static void updateStopsForLine(LineName line, vector<Station> &subwayStations);
};
#endif //M1OEP_NCYR1_SUBWAYMAP_H
