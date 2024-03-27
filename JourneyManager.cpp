//
// Created by Nolan Cyr on 3/21/24.
//

#include "JourneyManager.h"

JourneyManager::JourneyManager() {
    SubwayMap::createStations(NULL_TRAIN, allStations); // Fill allStations vector

    // Initialize startingStation and destinationStation with random stations
    startingStation = getRandomStation();
    destinationStation = getRandomStation();

    // Ensure startingStation and destinationStation are different
    while (startingStation == destinationStation) {
        destinationStation = getRandomStation();
    }
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

vector<Station> JourneyManager::getAllStations() {
    return allStations;
}

Station& JourneyManager::getRandomStation() {
    static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    static std::mt19937_64 generator1(seed);
    static std::default_random_engine generator2(generator1());
    static std::uniform_int_distribution<std::size_t> dist(0, allStations.size() - 1);

    std::size_t randomIndex = dist(generator2);

    return allStations[randomIndex];
}