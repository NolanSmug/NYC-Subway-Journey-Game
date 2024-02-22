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
        "Null_Train",
        "One_Train", "Two_Train", "Three_Train",
        "Four_Train", "Five_Train", "Six_Train", "Seven_Train",
        "A_Train", "C_Train", "E_Train",
        "B_Train", "D_Train", "F_Train", "M_Train",
        "N_Train", "Q_Train", "R_Train", "W_Train",
        "J_Train", "Z_Train",
        "G_Train",
        "L_Train"
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
    void updateStopsForLine(LineName line);

    vector<Station> getScheduledStops();
    void addScheduledStop(Station newStop);

    Station getCurrentStation();
    Station getNextStation();
    int getCurrentStationIndex();

    void setCurrentStation(int stationIndex);
    void setCurrentStation(string stationName);

    bool advanceStation();
    bool advanceStation(int numStations);

    bool isExpress();
    void setExpress(bool isExpress);

    int getNumCars();
    void setNumCars(int newNumCars);

    static string getTextForEnum(int enumVal);

private:
    LineName currentLine;
    LineName destinationLine; // users' desired line
    Direction direction;
    vector<Station> scheduledStops;
    int currentStationIndex = 0;
    bool express;
    int numCars; // not sure if this could be useful ever
};

#endif

