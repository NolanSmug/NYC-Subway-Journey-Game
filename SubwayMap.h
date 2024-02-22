//
// Created by Nolan Cyr on 2/1/24.
//
#ifndef M1OEP_NCYR1_SUBWAYMAP_H
#define M1OEP_NCYR1_SUBWAYMAP_H

#include <string>
#include <vector>
#include "Station.h"
#include "SubwayMap.h"
#include "Train.h"

using namespace std;

class SubwayMap {
private:
    vector<Station> allStations;

public:
    void createAllStations(string filePath, vector<Station>& allStations);

    void getStopsForLine(LineName line, vector<Station> &subwayStations);
};

#endif //M1OEP_NCYR1_SUBWAYMAP_H
