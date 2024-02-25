//
// Created by Nolan Cyr on 2/24/24.
//

#include "Line.h"
#include "Station.h"
#include "SubwayMap.h"
#include "Train.h"
#include <ctime>
#include <iostream>


bool test_all_classes();

int main() {
    srand(time(nullptr));
    if (test_all_classes()) {
        cout << "All Tests Passed!" << endl;
    }

    return 0;
}

bool test_all_classes() {
    bool passed = true;

    // Build Station vector with sample stations.
    Station timesSquare("id#000", "Times Square 42nd St", {ONE_TRAIN, TWO_TRAIN, THREE_TRAIN,
                                                                              N_TRAIN, Q_TRAIN, R_TRAIN, W_TRAIN});
    Station unionSquare("id#001", "14th St Union Square", {FOUR_TRAIN, FIVE_TRAIN, SIX_TRAIN,
                                                                             N_TRAIN, Q_TRAIN, R_TRAIN, W_TRAIN, L_TRAIN});
    vector<Station> testingStations;
    testingStations.push_back(timesSquare);
    testingStations.push_back(unionSquare);

    Train train = Train(ONE_TRAIN, BRONXBOUND, testingStations, false, 10);

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



    

    return passed;
}

