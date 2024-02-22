//
// Created by Nolan Cyr on 1/25/24.
//
#include "Train.h"

using namespace std;

Train::Train() : currentLine(NULL_TRAIN), direction(MANHATTANBOUND), scheduledStops(), express(false), numCars(10) {}

Train::Train(LineName currentLine, Direction direction, vector<Station> scheduledStops, bool express, int numCars) :
        currentLine(currentLine),
        direction(direction),
        scheduledStops(scheduledStops),
        express(express),
        numCars(numCars) {}

// Name
LineName Train::getName() {
    return currentLine;
}

void Train::setName(LineName newLineName) {
    currentLine = newLineName;
}

// Direction
Direction Train::getDirection() {
    return direction;
}

void Train::setDirection(Direction newDirection) {
    direction = newDirection;
}

// helper method for transferToLine()
// checks if users' requested LineName is at a specified Station
bool validTransfer(LineName &newLine, Station &currentStation) {
    vector<LineName> transfers = currentStation.getTransfers();

    for (LineName transferLine : transfers) {
        if (transferLine == newLine) {
            return true; // if found in the Station's transfer vector, valid
        }
    }

    return false;
}


bool Train::transferToLine(LineName newLine, Station currentStation) {
    bool valid = validTransfer(newLine, currentStation); // check if the new line is in the transfers vector

    // If the transfer is valid, proceed with the transfer
    if (valid) {
        setCurrentStation(currentStation.getName());
        updateScheduledStops(newLine);  // update the train's Station vector
        return true;
    }
    else {
        return false;
    }
}


void Train::updateScheduledStops(LineName line) {
    // TODO: update the Train objects' scheduledStops
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

void Train::setCurrentStation(int stationIndex) { // overloaded
    currentStationIndex = stationIndex;
}

void Train::setCurrentStation(string stationName) { // overloaded
    for (int i = 0; i < scheduledStops.size(); i++) {
        if (scheduledStops[i].getName() == stationName) { // TODO: Debug this. Will this actually work?
            setCurrentStation(i); // overloaded method
            break;
        }
    }
}

Station Train::getNextStation() {
    int increment = (direction == BRONXBOUND ? 1 : -1); // choose if we want
                                                        // to add or subtract to the index based on direction

    return scheduledStops[currentStationIndex == scheduledStops.size() - increment ? currentStationIndex : currentStationIndex + 1];
}

bool Train::advanceStation() {
    bool valid = currentStationIndex < scheduledStops.size();

    if (direction == BRONXBOUND) {
        currentStationIndex += (valid ? 1 : 0); // increment if uptown
    }
    else if (direction == MANHATTANBOUND) {
        currentStationIndex -= (valid ? 1 : 0); // decrement if downtown
    }
    else {
        valid = false; // ensure code doesn't break
    }
    setCurrentStation(currentStationIndex);

    return valid;
}

bool Train::advanceStation(int numStations) {
    bool valid;
    // valid flag needs to have a little more checks here for if the user enters an integer outside of the range
    // (which is also based on the direction of the train
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



