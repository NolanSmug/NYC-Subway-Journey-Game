//
// Created by Nolan Cyr on 1/25/24.
//
#include "Train.h"

#include <utility>

using namespace std;

Train::Train() : currentLine(NULL_TRAIN), direction(DOWNTOWN), scheduledStops(), express(false), numCars(10) {}

Train::Train(LineName currentLine, Direction direction, vector<Station> scheduledStops, bool express, int numCars) :
        currentLine(currentLine),
        direction(direction),
        scheduledStops(scheduledStops),
        express(express),
        numCars(numCars) {}

// Name
LineName Train::getLine() {
    return currentLine;
}

void Train::setLine(LineName newLineName) {
    currentLine = newLineName;
}

// Direction
Direction Train::getDirection() {
//    vector<Direction> directions = lineDirectionsMap[currentLine];

    return direction;
}

void Train::setDirection(Direction newDirection) {
    direction = newDirection;
}

// Transfer

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
    if (validTransfer(newLine, currentStation)) { // if the transfer is valid, proceed with the transfer
        updateScheduledStops(newLine); // update the Train's Station vector
        setCurrentStation(currentStation.getName()); // update the Train's currentStation
        currentLine = newLine; // update the Train's currentLine
        return true;
    }

    return false;  // not a valid requested transfer
}


void Train::updateScheduledStops(LineName &line) {
    SubwayMap subwayMap;
    subwayMap.updateStopsForLine(line, scheduledStops);
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

void Train::setCurrentStation(string stationName) {
    for (int i = 0; i < scheduledStops.size(); i++) {
        if (scheduledStops[i].getName() == stationName) {
            setCurrentStation(i);
            break;
        }
    }
}

Station Train::getNextStation() {
    int increment = (direction == UPTOWN ? 1 : -1); // choose if we want
                                                        // to add or subtract to the index based on direction

    return scheduledStops[currentStationIndex == scheduledStops.size() - increment ? currentStationIndex : currentStationIndex + 1];
}

bool Train::advanceStation() {
    bool valid = false;

    if (currentStationIndex < scheduledStops.size() - 1 || currentLine == S_TRAIN) {
        valid = true;

        if (direction == UPTOWN) {
            currentStationIndex++;
        }
        else if (direction == DOWNTOWN) {
            currentStationIndex--;
        }
    }

    setCurrentStation(currentStationIndex);
    return valid;
}


bool Train::advanceStation(int numStations) {
    bool valid = false;

    if (numStations <= 0) {
        return false;
    }

    if (direction == UPTOWN) {
        int newStationIndex = currentStationIndex + numStations;

        if (newStationIndex < scheduledStops.size()) {
            currentStationIndex = newStationIndex;
            valid = true;
        }
    }
    else if (direction == DOWNTOWN) {
        int newStationIndex = currentStationIndex - numStations;

        if (newStationIndex >= 0) {
            currentStationIndex = newStationIndex;
            valid = true;
        }
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

string Train::getTextForDirectionEnum(Direction direction, LineName line) {
    if (lineDirections.find(line) != lineDirections.end()) {
        return direction == DOWNTOWN ? lineDirections[line].first : lineDirections[line].second;
    }
}