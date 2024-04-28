//
// Created by Nolan Cyr on 3/11/24.
//

#ifndef NYC_SUBWAY_JOURNEY_GAME_CHALLENGE_H
#define NYC_SUBWAY_JOURNEY_GAME_CHALLENGE_H

#include <string>
#include "Line.h"
#include "Station.h"
#include "sstream"
#include <iomanip>

enum Difficulty {EASY, MEDIUM, HARD};

class Challenge {
public:
    Challenge();
    Challenge(Station startStation, Station destinationStation, Difficulty difficulty);

    LineName getStartLine();
    void setStartLine(LineName startLine);

    Station getStartStation();
    void setStartStation(Station newStartStation);

    Station getDestinationStation();
    void setDestinationStation(Station newDestinationStation);

    Difficulty getDifficulty();
    void setDifficulty(Difficulty difficulty);

    vector<Challenge> getAllChallenges();

    void initializeAllChallenges();
    void addNewChallenge(Challenge newChallenge);

    friend ostream& operator<<(ostream& str, Challenge challenge);


private:
    LineName startLine;
    Station startStation;
    Station destinationStation;
    Difficulty difficulty;
    vector<Challenge> allChallenges;
};


#endif //NYC_SUBWAY_JOURNEY_GAME_CHALLENGE_H
