//
// Created by Nolan Cyr on 1/25/24.
//
#include "Train.h"

unordered_map<LineName, pair<string, string>> lineDirections = {
        {ONE_TRAIN, {"Downtown", "Uptown"}},
        {TWO_TRAIN, {"Brooklyn-bound", "Bronx-bound"}},
        {THREE_TRAIN, {"Brooklyn-bound", "Bronx-bound"}},
        {FOUR_TRAIN, {"Brooklyn-bound", "Bronx-bound"}},
        {FIVE_TRAIN, {"Brooklyn-bound", "Bronx-bound"}},
        {SIX_TRAIN, {"Brooklyn-Bridge-bound", "Bronx-bound"}},
        {SEVEN_TRAIN, {"Manhattan-bound", "Queens-bound"}},
        {A_TRAIN, {"Downtown", "Uptown"}},
        {A_ROCKAWAY_MOTT_TRAIN, {"Far Rockaway–Mott Av", "Inwood 207-St"}},
        {A_LEFFERTS_TRAIN, {"Ozone Park–Lefferts Blvd", "Inwood 207-St"}},
        {B_TRAIN, {"Brooklyn-bound", "Manhattan-bound"}},
        {C_TRAIN, {"Brooklyn-bound", "Manhattan-bound"}},
        {D_TRAIN, {"Brooklyn-bound", "Bronx-bound"}},
        {E_TRAIN, {"Downtown", "Queens-bound"}},
        {F_TRAIN, {"Brooklyn-bound", "Queens-bound"}},
        {G_TRAIN, {"Church Av-bound", "Court Sq-bound"}},
        {J_TRAIN, {"Manhattan-bound", "Queens-bound"}},
        {L_TRAIN, {"Canarsie-Rockaway Pkwy-bound", "8 Av-bound"}},
        {M_TRAIN, {"Brooklyn-bound", "Queens-bound"}},
        {N_TRAIN, {"Brooklyn-bound", "Queens-bound"}},
        {Q_TRAIN, {"Brooklyn-bound", "Manhattan-bound"}},
        {R_TRAIN, {"Brooklyn-bound", "Manhattan-bound"}},
        {W_TRAIN, {"Manhattan-bound", "Queens-bound"}},
        {Z_TRAIN, {"Manhattan-bound", "Queens-bound"}},
        {S_TRAIN, {"Times Sq-bound", "Grand Central-bound"}},
        {S_TRAIN_SHUTTLE, {"Franklin Av-bound", "Prospect Park-bound"}},
        {S_TRAIN_ROCKAWAY, {"Broad Channel-bound", "Rockaway Park-Beach 116 St-bound"}
    }
};

unordered_map<LineName, LineType> lineTypes = {
    {ONE_TRAIN, LOCAL},
    {TWO_TRAIN, EXPRESS},
    {THREE_TRAIN, EXPRESS},
    {FOUR_TRAIN, EXPRESS},
    {FIVE_TRAIN, EXPRESS},
    {SIX_TRAIN, LOCAL},
    {SEVEN_TRAIN, LOCAL},
    {A_TRAIN, EXPRESS},
    {B_TRAIN, EXPRESS},
    {C_TRAIN, LOCAL},
    {D_TRAIN, EXPRESS},
    {E_TRAIN, EXPRESS},
    {F_TRAIN, LOCAL},
    {G_TRAIN, LOCAL},
    {J_TRAIN, LOCAL},
    {L_TRAIN, LOCAL},
    {M_TRAIN, LOCAL},
    {N_TRAIN, EXPRESS},
    {Q_TRAIN, EXPRESS},
    {R_TRAIN, LOCAL},
    {W_TRAIN, LOCAL},
    {Z_TRAIN, LOCAL},
    {S_TRAIN, NONE},
    {S_TRAIN_SHUTTLE, NONE},
    {S_TRAIN_ROCKAWAY, NONE}
};



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

void Train::setScheduledStops(vector<Station> newScheduledStops) {
    scheduledStops = newScheduledStops;
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
        if (reversedScheduledStops[i].getId() == station.getId()) {
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
    if (direction == UPTOWN) {
        currentStationIndex++;
    }
    else if (direction == DOWNTOWN) {
        currentStationIndex--;
    }
    else {
        return false;
    }

    setCurrentStation(currentStationIndex);
    return true;
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
