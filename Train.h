//
// Created by Nolan Cyr on 1/25/24.
//
#ifndef TRAIN_H
#define TRAIN_H

#include <string>
#include <vector>
#include "Train.h"
#include "Station.h"

using namespace std;

class Train {
public:
    enum Direction {QUEENSBOUND, MANHATTANBOUND, BRONXBOUND};

    Train();
    Train(string lineName, Direction direction, vector<Station> scheduledStops, bool express, int numCars);

    string getName();
    void setName(string newName);

    Direction getDirection();
    void setDirection(Direction newDirection);

    vector<Station> getScheduledStops();
    void addScheduledStop(Station newStop);

    Station getCurrentStation();
    int getCurrentStationIndex();
    void setCurrentStation(int stationIndex);
    Station getNextStation();
    bool advanceStation();
    bool advanceStation(int numStations);

    bool isExpress();
    void setExpress(bool isExpress);

    int getNumCars();
    void setNumCars(int newNumCars);

private:
    string lineName;
    Direction direction;
    vector<Station> scheduledStops;
    int currentStationIndex = 0;
    bool express;
    int numCars; // not sure if this could be useful ever
};

#endif

