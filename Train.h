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

    string getName() const;
    void setName(const string& newName);

    Direction getDirection();
    void setDirection(const Direction& newDirection);

    vector<Station> getScheduledStops() const;
    void addScheduledStops(const Station& newStop);

    bool isExpress() const;
    void setExpress(bool isExpress);

    int getNumCars() const;
    void setNumCars(int newNumCars);

private:
    string lineName;
    Direction direction;
    vector<Station> scheduledStops;
    bool express;
    int numCars;
};

#endif

