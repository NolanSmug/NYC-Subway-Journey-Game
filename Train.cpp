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
string Train::getName() {
    return lineName;
}

void Train::setName(string newName) {
    lineName = newName;
}

// Direction
Train::Direction Train::getDirection() {
    return direction;
}

void Train::setDirection(Direction newDirection) {
    direction = newDirection;
}

// Scheduled Stops
vector<Station> Train::getScheduledStops()  {
    return scheduledStops;
}

void Train::addScheduledStop(Station newStop) {
    scheduledStops.push_back(newStop);
}

// Current Stations
Station Train::getCurrentStation() {
    return scheduledStops[currentStationIndex];
}

int Train::getCurrentStationIndex() {
    return currentStationIndex;
}

void Train::setCurrentStation(int stationIndex) {
    currentStationIndex = stationIndex;
}

Station Train::getNextStation() {
    int increment = (direction == BRONXBOUND ? 1 : -1);

    return scheduledStops[currentStationIndex == scheduledStops.size() - increment ? currentStationIndex : currentStationIndex + 1];
}

bool Train::advanceStation() {
    bool valid = currentStationIndex < scheduledStops.size();

    if (direction == BRONXBOUND) {
        currentStationIndex += (valid ? 1 : 0);
    } else if (direction == MANHATTANBOUND) {
        currentStationIndex -= (valid ? 1 : 0);
    }
    setCurrentStation(currentStationIndex);

    return valid;
}

bool Train::advanceStation(int numStations) {
    bool valid;

    if (direction == BRONXBOUND) {
        valid = (currentStationIndex + numStations < scheduledStops.size()) && (numStations > 0);
        currentStationIndex += (valid ? numStations : 0);
    }
    else if (direction == MANHATTANBOUND) {
        valid = (currentStationIndex - numStations < scheduledStops.size()) && (numStations > 0);
        currentStationIndex -= (valid ? numStations : 0);
    }
    else {
        valid = false;
    }
    setCurrentStation(currentStationIndex);

    return valid;
}

// Express
bool Train::isExpress() {
    return express;
}

void Train::setExpress(bool isExpress) {
    express = isExpress;
}

// Number of Cars
int Train::getNumCars() {
    return numCars;
}

void Train::setNumCars(int newNumCars) {
    numCars = newNumCars;
}
