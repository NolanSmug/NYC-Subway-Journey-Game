//
// Created by Nolan Cyr on 1/25/24.
//

#include "Train.h"

using namespace std;

Train::Train() : lineName(), direction(MANHATTANBOUND), scheduledStops(), express(false), numCars(10) {}

Train::Train(string lineName, Direction direction, vector<Station> scheduledStops, bool express, int numCars) :
        lineName(lineName),
        direction(direction),
        scheduledStops(scheduledStops),
        express(express),
        numCars(numCars) {}

// Name
string Train::getName() const {
    return lineName;
}

void Train::setName(const string& newName) {
    lineName = newName;
}

// Direction
Train::Direction Train::getDirection() {
    return direction;
}

void Train::setDirection(const Train::Direction& newDirection) {
    direction = newDirection;
}

// Scheduled Stops
vector<Station> Train::getScheduledStops() const {
    return scheduledStops;
}

void Train::addScheduledStops(const Station& newStop) {
    scheduledStops.push_back(newStop);
}

// Express
bool Train::isExpress() const {
    return express;
}

void Train::setExpress(bool isExpress) {
    express = isExpress;
}

// Number of Cars
int Train::getNumCars() const {
    return numCars;
}

void Train::setNumCars(int newNumCars) {
    numCars = newNumCars;
}
