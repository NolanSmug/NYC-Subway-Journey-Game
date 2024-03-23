//
// Created by Nolan Cyr on 3/21/24.
//

#include "JourneyManager.h"

JourneyManager::JourneyManager() {
    SubwayMap::createStations(NULL_TRAIN, allStations); // Fill allStations vector
    startingStation = allStations[0];
    destinationStation = allStations[allStations.size()];

}

JourneyManager::JourneyManager(Station startingStation, Station destinationStation) {
    this->startingStation = startingStation;
    this->destinationStation = destinationStation;

    SubwayMap::createStations(NULL_TRAIN, allStations); // Fill allStations vector
}


Station JourneyManager::getStartingStation() {
    return startingStation;
}

void JourneyManager::setStartingStation(Station newStartingStation) {
    startingStation = newStartingStation;
}

void JourneyManager::setStartingStation(string newStartingStation) { // works for name or id
    for (Station station : allStations) {
        string id = station.getId();
        string name = station.getName();

        if (newStartingStation == id || newStartingStation == name) {
            startingStation = station;
             break;
        }
    }
}


Station JourneyManager::getDestinationStation() {
    return destinationStation;
}

void JourneyManager::setDestinationStation(Station newDestinationStation) {
    destinationStation = newDestinationStation;
}

void JourneyManager::setDestinationStation(string newDestinationStation) { // works for name or id
    for (Station station : allStations) {
        string id = station.getId();
        string name = station.getName();

        if (newDestinationStation == id || newDestinationStation == name) {
            destinationStation = station;
            break;
        }
    }
}




