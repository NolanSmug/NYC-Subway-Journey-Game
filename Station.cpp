//
// Created by Nolan Cyr on 1/31/24.
//

#include "Station.h"

using namespace std;

Station::Station() : name(), transfers() {}

Station::Station(string name, vector<string> transfers):
        name(name),
        transfers(transfers) {}

string Station::getName() {
    return name;
}

void Station::setName(const string& newName) {
    name = newName;
}

vector<string> Station::getTransfers() {
    return transfers;
}

void Station::addTransfers(const string& newTransfer) {
    transfers.push_back(newTransfer);
}
