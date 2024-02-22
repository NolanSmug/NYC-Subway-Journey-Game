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


bool Train::transferToLine(LineName newLine, Station currentStation) {
    vector<string> transfers = currentStation.getTransfers();

    // check if the new line is in the transfers vector
    bool validTransfer = false;
    for (const auto& transferLine : transfers) {
        if (transferLine == LineEnumStrings[newLine]) { // TODO: right now this won't work. need some way to compare line enum
            validTransfer = true;
            break;
        }
    }

    // If the transfer is valid, proceed with the transfer
    if (validTransfer) {
        setCurrentStation(currentStation.getName());

        // update the stops
        updateStopsForLine(newLine);
        return true;
    }
    else {
        return false;
    }
}

void Train::updateStopsForLine(LineName line) {
//    vector<Station> newStops = subwayMap.getStopsForLine(line);

//    scheduledStops = newStops;

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

string Train::getTextForEnum(int enumVal) {
    return LineEnumStrings[enumVal];
}
