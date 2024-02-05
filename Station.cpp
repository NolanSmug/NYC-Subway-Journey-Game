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

Station::Station(string id, string name, vector<string> transfers, Borough borough) :
        id(id),
        name(name),
        transfers(transfers),
        borough(borough) {}

// overloaded cout operator
ostream& operator<<(ostream& str, Station station) {
    str << "Name: " << station.getName() << endl;
//    str << "ID: " << station.getId() << endl; // should I bother printing the ID?
    str << "Transfer Available to the: ";
    for (string line : station.getTransfers()) {
        str << line << (station.getTransfers().size() == 1 ? "" : ", ");
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
string Station::getName() {
    return name;
}

void Station::setName(string newName) {
    name = newName;
}

// Transfers
vector<string> Station::getTransfers() {
    return transfers;
}

void Station::addTransfers(string newTransfer) {
    transfers.push_back(newTransfer);
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
const string Station::getTextForEnum(int enumVal) {
    return EnumStrings[enumVal];
}
