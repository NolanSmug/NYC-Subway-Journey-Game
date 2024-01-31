#include <iostream>
#include "Train.h"
#include "Station.h"

using namespace std;


int main() {
    Station rector = Station("Rector St", {"1"});
    vector<Station> oneTrainStations;
    oneTrainStations.push_back(rector);

    Train oneLine = Train("1 Train", Train::MANHATTANBOUND, oneTrainStations, false, 10);
}
