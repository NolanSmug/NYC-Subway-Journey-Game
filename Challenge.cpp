
#include "Challenge.h"

Challenge::Challenge() = default;

Challenge::Challenge(LineName startLine, string startStationName, string destinationStationName, int difficulty) :
    startLine(startLine),
    startStationName(startStationName),
    destinationStationName(destinationStationName),
    difficulty() {}


void Challenge::setStartLine(LineName newStartLine) {
    startLine = newStartLine;
}

LineName Challenge::getStartLine() {
    return startLine;
}


void Challenge::setStartStationName(string newStartStation) {
    startStationName = newStartStation;
}

string Challenge::getStartStationName() {
    return startStationName;
}


void Challenge::setDestinationStationName(string newDestinationStation) {
    destinationStationName = newDestinationStation;
}

string Challenge::getDestinationStationName() {
    return destinationStationName;
}


int Challenge::getDifficulty() {
    return difficulty;
}

void Challenge::setDifficulty(int newDifficulty) {
    difficulty = newDifficulty;
}


vector<Challenge> initializeChallenges() {
    vector<Challenge> allChallenges;

    // Easy challenges
    allChallenges.emplace_back(FOUR_TRAIN, "Grand Central-42 St", "Brooklyn Bridge-City Hall", 1);
    allChallenges.emplace_back(TWO_TRAIN, "96th St", "Flatbush Ave-Brooklyn College", 1);
    allChallenges.emplace_back(E_TRAIN, "34 St-Penn Station", "World Trade Center",1);
    allChallenges.emplace_back(G_TRAIN, "Metropolitan Ave", "Court Sq", 1);
    allChallenges.emplace_back(SEVEN_TRAIN, "Grand Central-42 St","Mets-Willets Point",1);

    // Medium challenges
    allChallenges.emplace_back(ONE_TRAIN, "Van Cortlandt Park-242nd St", "World Trade Center", 2);
    allChallenges.emplace_back(N_TRAIN, "Astoria-Ditmars Blvd", "Prince St", 2);
    allChallenges.emplace_back(FIVE_TRAIN, "14 St-Union Sq", "Howard Beach-JFK Airport", 2);
    allChallenges.emplace_back(B_TRAIN, "81 St-Museum of Natural History", "Delancey St-Essex St", 2);
    allChallenges.emplace_back(M_TRAIN, "Myrtle Av", "Nostrand Av", 2);

    // Hard challenges
    allChallenges.emplace_back(G_TRAIN, "Court Sq", "Dyckman St", 3);
    allChallenges.emplace_back(SIX_TRAIN, "Pelham Bay Park", "Coney Island-Stillwell Ave", 3);
    allChallenges.emplace_back(ONE_TRAIN, "Dyckman St", "Greenpoint Av", 3);
    allChallenges.emplace_back(A_TRAIN, "Far Rockaway-Mott Av", "Jamaica-179 St", 3);
    // does there exist one that requires 3+ transfers?

    return allChallenges;
}


