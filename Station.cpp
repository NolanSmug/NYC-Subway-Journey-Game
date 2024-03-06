//
// Created by Nolan Cyr on 1/31/24.
//

#include "Station.h"
#include "sstream"
#include <fstream>
using std::ifstream, std::string, std::vector;

using namespace std;

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
    str << "Transfer Available to the: ";
    for (LineName line : station.getTransfers()) {
        str << Line::getTextForEnum(line) << (station.getTransfers().size() == 1 ? "" : " ");
    }
    str << endl;
    str << "Borough: " << station.getTextForEnum(station.getBorough()) << endl;
    str << "\n";

    return str;
}

// ID
string Station::getId() {
    return id;
}

void Station::setId(string newId) {
    id = newId;
}

// Name
string Station::getName() const {
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
    return Line::getTextForEnum(enumVal);
}
