//
// Created by Nolan Cyr on 1/25/24.
//
#ifndef TRAIN_H
#define TRAIN_H

#include <string>
#include <vector>
#include "Station.h"
#include "Line.h"
#include "SubwayMap.h"

using namespace std;
enum Direction {BRONXBOUND, MANHATTANBOUND, QUEENSBOUND, BROOKLYNBOUND};

static const char * DirectionEnumStrings[] = {
        "Bronx-Bound", "Manhattan-Bound", "Queens-Bound", "Brooklyn-Bound"
};

class Train {
public:
    Train();
    Train(LineName lineName, Direction direction, vector<Station> scheduledStops, bool express, int numCars);

    LineName getName();
    void setName(LineName newLineName);

    Direction getDirection();
    void setDirection(Direction newDirection);

    bool transferToLine(LineName newLine, Station currentStation);
    void updateScheduledStops(LineName &line);

    vector<Station> getScheduledStops();
    void addScheduledStop(Station newStop);

    Station getCurrentStation();
    Station getNextStation();
    int getCurrentStationIndex();

    void setCurrentStation(int stationIndex);   // overloaded
    void setCurrentStation(string stationName); // overloaded

    bool advanceStation();                  // overloaded
    bool advanceStation(int numStations);   // overloaded

    bool isExpress();
    void setExpress(bool isExpress);

    int getNumCars();
    void setNumCars(int newNumCars);

    static string getTextForEnum(int enumVal);

private:
    LineName currentLine;
    Direction direction;
    vector<Station> scheduledStops;
    int currentStationIndex = 0;
    bool express;
    int numCars; // not sure if this could be useful ever
};

#endif
