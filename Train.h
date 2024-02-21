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
enum Direction {QUEENSBOUND, MANHATTANBOUND, BRONXBOUND};
enum LineName { NULL_TRAIN,
    ONE_TRAIN, TWO_TRAIN, THREE_TRAIN,
    FOUR_TRAIN, FIVE_TRAIN, SIX_TRAIN, SEVEN_TRAIN,
    A_TRAIN, C_TRAIN, E_TRAIN,
    B_TRAIN, D_TRAIN, F_TRAIN, M_TRAIN,
    N_TRAIN, Q_TRAIN, R_TRAIN, W_TRAIN,
    J_TRAIN, Z_TRAIN,
    G_TRAIN,
    L_TRAIN
};

static const char * LineEnumStrings[] = {
        "Null Train",
        "One Train", "Two Train", "Three Train",
        "Four Train", "Five Train", "Six Train", "Seven Train",
        "A Train", "C Train", "E Train",
        "B Train", "D Train", "F Train", "M Train",
        "N Train", "Q Train", "R Train", "W Train",
        "J Train", "Z Train",
        "G Train",
        "L Train"
};


class Train {
public:
    Train();
    Train(LineName lineName, Direction direction, vector<Station> scheduledStops, bool express, int numCars);

    LineName getName();
    void setName(LineName newLineName);

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

    string getTextForEnum(int enumVal);

private:
    LineName lineName;
    Direction direction;
    vector<Station> scheduledStops;
    int currentStationIndex = 0;
    bool express;
    int numCars; // not sure if this could be useful ever
};

#endif

