//
// Created by Nolan Cyr on 1/31/24.
//

#include "Station.h"
#include "sstream"

using namespace std;

Station::Station() : id(), name(), transfers(), borough(MANHATTAN) {}

Station::Station(string id, string name, vector<string> transfers, Borough borough) :
        id(id),
        name(name),
        transfers(transfers),
        borough(borough) {}

// ID
string Station::getId() {
    return id;
}

void Station::setId(const string& newId) {
    id = newId;
}

// Name
string Station::getName() {
    return name;
}

void Station::setName(const string& newName) {
    name = newName;
}

// Transfers
vector<string> Station::getTransfers() {
    return transfers;
}

void Station::addTransfers(const string& newTransfer) {
    transfers.push_back(newTransfer);
}

// Borough
Borough Station::getBorough() {
    return borough;
}

void Station::setBorough(Borough newBorough) {
    borough = newBorough;
}
