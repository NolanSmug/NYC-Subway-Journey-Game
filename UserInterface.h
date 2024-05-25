//
// Created by Nolan Cyr on 5/18/24.
//

#ifndef NYC_SUBWAY_JOURNEY_GAME_USERINTERFACE_H
#define NYC_SUBWAY_JOURNEY_GAME_USERINTERFACE_H

#include "Train.h"
#include "Challenge.h"
#include "GameState.h"
#include <iostream>
#include <thread>

// UserInterface.h
class UserInterface {
public:
    void displayCurrentStationInfo(Train train);
    void displayDestinationStationInfo(Station destinationStation);
    void displayUpcomingStations(Train train);
    void displayStationsFor(vector<Station> stations);
    void displayCurrentLineInfo(Train train);
    void displayAllChallenges(Challenge challenge);
    void displayGameWin(Train train, GameStats stats);
    void displayTransferSuccess(Train train);
    void displayAvailableTrainActions(Train train, GameState gameState);
    void displayGameReset();
    void displayDirectionChange(Train train);

    void announceLastStop(Train train);
};


#endif //NYC_SUBWAY_JOURNEY_GAME_USERINTERFACE_H
