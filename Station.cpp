//
// Created by Nolan Cyr on 1/31/24.
//

#include "Station.h"
#include "SubwayMap.h"
#include "sstream"

// Constructors
Station::Station() : id(), name(), transfers(), borough(MANHATTAN) {}

Station::Station(string id, string name, vector<LineName> transfers, Borough borough) :
        id(id),
        name(name),
        transfers(transfers),
        borough(borough) {}

// overloaded cout operator
ostream& operator<<(ostream& str, Station station) {
    str << "Name: " << station.getName() << endl;
//  str << "ID: " << station.getId() << endl; // should I bother printing the ID?
    str << "Transfer Available to the:";
    str << station.getTransferLinesString();
    str << endl;
    str << "Borough: " << Station::getTextForEnum(station.getBorough()) << endl;
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

vector<Station> getAllStations() {
    vector<Station> allStations;
    SubwayMap::createStations(NULL_TRAIN,allStations);
    return allStations;
}

Station Station::getStation(string stationName, string stationID) {
    for (Station station : getAllStations()) {
        if (station.getId() == stationID || station.getName() == stationName) {
            return station;
        }
    }

    return Station("000", "NULL_STATION", {NULL_TRAIN});
}
