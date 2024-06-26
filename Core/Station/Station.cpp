//
// Created by Nolan Cyr on 1/31/24.
//

#include "Station.h"

// Constructors
Station::Station() : id(), name(), transfers(), borough(MANHATTAN) {}

Station::Station(string id, string name, vector<LineName> transfers, Borough borough) :
        id(id),
        name(name),
        transfers(transfers),
        borough(borough) {}


vector<Station> Station::allNycStations;
// In Station.cpp
void Station::initializeAllStations() {
    if (allNycStations.empty()) {
        SubwayMap::createStations(NULL_TRAIN, allNycStations);
    }
}

// overloaded cout operator
ostream& operator<<(ostream& str, Station station) {
    str << "\t" << station.getName() << endl;
//  str << "ID: " << station.getId() << endl; // should I bother printing the ID?
    str << "\tTransfer Available to the:";
    str << station.getTransferLinesString();
    str << endl;
    str << "\tBorough: " << Station::getTextForEnum(station.getBorough()) << endl;
    str << "\n";

    return str;
}

// equals operator
bool Station::operator==(const Station &rhs) const {
    return name == rhs.name && transfers == rhs.transfers;
}

bool Station::operator!=(const Station &rhs) const {
    return !(rhs == *this);
}

// ID
string Station::getId(){
    return id;
}

void Station::setId(string newId) {
    id = newId;
}

// Name
string Station::getName() {
    return name;
}

void Station::setName(string newName) {
    name = newName;
}

// Transfers
vector<LineName> Station::getTransfers() {
    return transfers;
}

vector<Station> Station::getAllStations() {
    return allNycStations;
}

void Station::addTransfers(LineName newTransfer) {
    transfers.push_back(newTransfer);
}

bool Station::hasTransferLine(string input) {
    for (LineName line : transfers) {
        if (Line::getTextForEnum(line) == input) {
            return true;
        }
    }
    return false;
}

bool Station::hasTransferLine() {
    return transfers.size() > 1;
}

string Station::getTransferLinesString() {
    unsigned int numTransfers = transfers.size();
    string transferLinesStr = "";

    if (numTransfers > 0) {
        transferLinesStr += " (";
        for (int i = 0; i < numTransfers; ++i) {
            transferLinesStr += Line::getTextForEnum(transfers[i]);
            if (i != numTransfers - 1) { // If it's not the last line, add a space
                transferLinesStr += " ";
            }
        }
        transferLinesStr += ") ";
    }

    return transferLinesStr;
}


// Borough
Borough Station::getBorough() {
    return borough;
}

void Station::setBorough(Borough newborough) {
    borough = newborough;
}

// pattern for enum toString() found on StackOverflow
// https://stackoverflow.com/a/6281535
string Station::getTextForEnum(int enumVal) {
    return BoroughEnumStrings[enumVal];
}


Station Station::getStation(string stationID) {
    for (Station station : allNycStations) {
        if (station.getId() == stationID) {
            return station;
        }
    }

    return Station("000", "NULL_STATION", {NULL_TRAIN},MANHATTAN);
}

Station Station::getRandomStation(vector<Station> &stations) {
    // Ensure there is at least one station in the vector
    if (stations.empty()) {
        throw std::runtime_error("Station vector is empty");
    }

    // Seed the random number generator only once
    static std::random_device rd;
    static std::mt19937 generator(rd());

    // Create a uniform distribution from 0 to stations.size() - 1
    std::uniform_int_distribution<size_t> dist(0, stations.size() - 1);

    // Generate a random index
    size_t randomIndex = dist(generator);

    return stations[randomIndex];
}
