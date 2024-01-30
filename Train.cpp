//
// Created by Nolan Cyr on 1/25/24.
//

#include "Train.h"

using namespace std;

Train::Train() : express(false), numCars(10) {}

Train::Train(string lineName, vector<string> scheduledStops, bool express, int numCars)
        : lineName(lineName), scheduledStops(scheduledStops), express(express), numCars(numCars) {}

string Train::getLineName() const {
    return lineName;
}

void Train::setLineName(const string& newLineName) {
    lineName = newLineName;
}

vector<string> Train::getScheduledStops() const {
    return scheduledStops;
}

void Train::addScheduledStops(const string& newStop) {
    scheduledStops.push_back(newStop);
}

bool Train::isExpress() const {
    return express;
}

void Train::setExpress(bool isExpress) {
    express = isExpress;
}

int Train::getNumCars() const {
    return numCars;
}

void Train::setNumCars(int newNumCars) {
    numCars = newNumCars;
}
