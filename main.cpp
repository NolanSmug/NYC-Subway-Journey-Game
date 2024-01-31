#include <iostream>
#include "Train.h"
#include "Station.h"

using namespace std;

const vector<string> ONE_TRAIN_STOPS = {
        "South Ferry",
        "Rector St",
        "Cortlandt St",
        "Chambers St - World Trade Center",
        "Franklin St",
        "Canal St",
        "Houston St",
        "Christopher St - Sheridan Sq",
        "14 St",
        "18 St",
        "23 St",
        "28 St",
        "34 St - Penn Station",
        "Times Sq - 42 St",
        "50 St",
        "59 St - Columbus Circle",
        "66 St - Lincoln Center",
        "72 St",
        "79 St",
        "86 St",
        "96 St",
        "103 St",
        "110 St",
        "116 St - Columbia University",
        "125 St",
        "137 St - City College",
        "145 St",
        "157 St",
        "168 St - Washington Hts",
        "181 St",
        "191 St",
        "Dyckman St",
        "207 St",
        "215 St",
        "Marble Hill - 225 St",
        "231 St",
        "238 St",
        "242 St",
        "Van Cortlandt Park - 242 St"
};


int main() {
    Station rector = Station("Rector St.", {"1"});
    vector<Station> oneTrainStations;
    oneTrainStations.push_back(rector);

    Train oneLine = Train("1 Train", Train::BRONXBOUND, oneTrainStations, false, 10);}
