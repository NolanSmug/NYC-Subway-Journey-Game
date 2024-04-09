//
// Created by Nolan Cyr on 3/21/24.
//

#ifndef NYC_SUBWAY_JOURNEY_GAME_JOURNEYMANAGER_H
#define NYC_SUBWAY_JOURNEY_GAME_JOURNEYMANAGER_H

#include "Station.h"
#include "random"
#include "SubwayMap.h"


class JourneyManager {
public:
    JourneyManager();
    JourneyManager(Station newStartingStation, Station newDestinationStation);

    Station getStartingStation();
    void setStartingStation(Station newStartingStation);
    void setStartingStation(string newStartingStation);

    Station getDestinationStation();
    void setDestinationStation(Station newDestinationStation);
    void setDestinationStation(string newDestinationStation);

    static vector<Station> getAllStations();

    Station& getRandomStation();

private:
    static vector<Station> allStations;
    Station startingStation;
    Station destinationStation;
};

#endif //NYC_SUBWAY_JOURNEY_GAME_JOURNEYMANAGER_H

