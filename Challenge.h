//
// Created by Nolan Cyr on 3/11/24.
//

#ifndef NYC_SUBWAY_JOURNEY_GAME_CHALLENGE_H
#define NYC_SUBWAY_JOURNEY_GAME_CHALLENGE_H

#include <string>
#include "Line.h"

class Challenge {
public:
    Challenge();
    Challenge(LineName startLine, string startStationName, string destinationStationName, int difficulty);

    LineName getStartLine();
    void setStartLine(LineName startLine);

    string getStartStationName();
    void setStartStationName(string startStationName);

    string getDestinationStationName();
    void setDestinationStationName(string destinationStationName);

    int getDifficulty();
    void setDifficulty(int difficulty);


private:
    LineName startLine;
    string startStationName;
    string destinationStationName;
    int difficulty;
};


#endif //NYC_SUBWAY_JOURNEY_GAME_CHALLENGE_H
