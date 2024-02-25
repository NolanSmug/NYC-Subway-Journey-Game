//
// Created by Nolan Cyr on 2/24/24.
//

#include "Line.h"
#include "Station.h"
#include "SubwayMap.h"
#include "Train.h"
#include <ctime>
#include <iostream>


bool test_train_class();
bool test_station_class();

int main() {
    srand(time(nullptr));
    if (test_train_class()) {
        cout << "Train Tests Passed!" << endl;
    }
    if (test_station_class()) {
        cout << "Station Tests Passed!" << endl;
    }

    return 0;
}

bool test_train_class() {
    bool passed = true;

    // Build Station vector with sample stations.
    Station timesSquare("id#000", "Times Square 42nd St", {ONE_TRAIN, TWO_TRAIN, THREE_TRAIN,
                                                                              N_TRAIN, Q_TRAIN, R_TRAIN, W_TRAIN});
    Station unionSquare("id#001", "14th St Union Square", {FOUR_TRAIN, FIVE_TRAIN, SIX_TRAIN,
                                                                             N_TRAIN, Q_TRAIN, R_TRAIN, W_TRAIN, L_TRAIN});
    vector<Station> testingStations;
    testingStations.push_back(timesSquare);
    testingStations.push_back(unionSquare);

    Train train = Train(FOUR_TRAIN, BRONXBOUND, testingStations, false, 10);

    train.setCurrentStation(0);
    if (train.getCurrentStation().getName() != "Times Square 42nd St") {
        passed = false;
        cout << "setCurrentStation(int) test failed" << endl;
    }

    train.setCurrentStation("14th St Union Square");
    if (train.getCurrentStation().getName() != "14th St Union Square") {
        passed = false;
        cout << "setCurrentStation(string) test failed" << endl;
    }

    train.setCurrentStation(0);
    if (train.getNextStation().getName() != "14th St Union Square") {
        passed = false;
        cout << "getNextStation() test failed" << endl;
    }

    train.advanceStation();
    if (train.getCurrentStation().getName() != "14th St Union Square") {
        passed = false;
        cout << "getNextStation() test failed" << endl;
    }

    if (!train.transferToLine(SIX_TRAIN, unionSquare)) {
        passed = false;
        cout << "transferToLine() test failed" << endl;
    }

    return passed;
}

bool test_station_class() {
    bool passed = true;

    // Create a sample Station
    Station station("id#001", "14th St Union Square", {FOUR_TRAIN, FIVE_TRAIN, SIX_TRAIN,
                                                       N_TRAIN, Q_TRAIN, R_TRAIN, W_TRAIN, L_TRAIN});

    if (station.getName() != "14th St Union Square") {
        passed = false;
        cout << "getName() test failed" << endl;
    }

    station.setName("New Station Name");
    if (station.getName() != "New Station Name") {
        passed = false;
        cout << "setName() test failed" << endl;
    }

    vector<LineName> transfers = station.getTransfers();
    if (transfers.size() != 8) { // Assuming the sample station has 8 transfers
        passed = false;
        cout << "getTransfers() test failed" << endl;
    }

    station.addTransfers(THREE_TRAIN);
    transfers = station.getTransfers();
    if (transfers.size() != 9) {
        passed = false;
        cout << "addTransfers() test failed" << endl;
    }

    if (station.getBorough() != MANHATTAN) {
        passed = false;
        cout << "getBorough() test failed" << endl;
    }

    station.setBorough(BRONX);
    if (station.getBorough() != BRONX) {
        passed = false;
        cout << "setBorough() test failed" << endl;
    }

    return passed;
}


