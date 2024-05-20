//
// Created by Nolan Cyr on 5/18/24.
//

#ifndef NYC_SUBWAY_JOURNEY_GAME_USERINTERFACE_H
#define NYC_SUBWAY_JOURNEY_GAME_USERINTERFACE_H

#include "Game.h"

// UserInterface.h
class UserInterface {
public:
    void displayCurrentStationInfo(Train train);
    void displayCurrentLineInfo(Train train);
    void displayDestinationStationInfo(Station destinationStation);
    void displayUpcomingStations(Train train);
    void displayAllChallenges(Challenge challenge);
    void displayStationsFor(vector<Station> stations);

    void announceLastStop(Train &train); // must update the train here

};


#endif //NYC_SUBWAY_JOURNEY_GAME_USERINTERFACE_H
