//
// Created by Nolan Cyr on 3/11/24.
//

#ifndef NYC_SUBWAY_JOURNEY_GAME_CHALLENGE_H
#define NYC_SUBWAY_JOURNEY_GAME_CHALLENGE_H

#include <string>
#include "Line.h"
#include "Station.h"

class Challenge {
public:
    Challenge();
    Challenge(LineName startLine, Station startStation, Station destinationStation, int difficulty);

    LineName getStartLine();
    void setStartLine(LineName startLine);

    Station getStartStation();
    void setStartStation(Station newStartStation);

    Station getDestinationStation();
    void setDestinationStation(Station newDestinationStation);

    int getDifficulty();
    void setDifficulty(int difficulty);

    vector<Challenge> getAllChallenges();


private:
    LineName startLine;
    Station startStation;
    Station destinationStation;
    int difficulty;
};


#endif //NYC_SUBWAY_JOURNEY_GAME_CHALLENGE_H
