//
// Created by Nolan Cyr on 1/25/24.
//
#include "Train.h"

Train::Train() : currentLine(NULL_TRAIN), direction(NULL_DIRECTION), scheduledStops(), lineType(NONE), numCars(10) {}

Train::Train(LineName lineName, Direction direction, vector<Station> scheduledStops, LineType lineType, int numCars)
        : currentLine(lineName), direction(direction), scheduledStops(scheduledStops), lineType(lineType), numCars(numCars) {
    uptownLabel = getTextForDirectionEnum(UPTOWN, lineName);
    downtownLabel = getTextForDirectionEnum(DOWNTOWN, lineName);
}

// Name
LineName Train::getLine() {
    return currentLine;
}

void Train::setLine(LineName newLineName) {
    currentLine = newLineName;
}

// Direction
Direction Train::getDirection() {
    return direction;
}

void Train::setDirection(Direction newDirection) {
    direction = newDirection;
}

// Direction Labels (strings)
string Train::getUptownLabel() {
    return uptownLabel;
}

string Train::getDowntownLabel() {
    return downtownLabel;
}

void Train::setUptownLabel(string newLabel) {
    uptownLabel = newLabel;
}

void Train::setDowntownLabel(string newLabel) {
    downtownLabel = newLabel;
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
        uptownLabel = getTextForDirectionEnum(UPTOWN, newLine);
        downtownLabel = getTextForDirectionEnum(DOWNTOWN, newLine);

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

void Train::setCurrentStation(Station station) {
    vector<Station> reversedScheduledStops(scheduledStops.rbegin(), scheduledStops.rend());

    for (int i = 0; i < reversedScheduledStops.size(); i++) {
        if (reversedScheduledStops[i] == station) {
            currentStationIndex = scheduledStops.size() - i - 1;
            break;
        }
    }
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

LineType Train::setLineType() {
    auto lineTypeIter = lineTypes.find(currentLine);
    if (lineTypeIter != lineTypes.end()) {
        return lineTypeIter->second;
    }
    else {
        return NONE;
    }
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
    return {};
}
