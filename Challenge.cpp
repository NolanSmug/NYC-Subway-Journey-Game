
#include "Challenge.h"
#include <fstream>

Challenge::Challenge() = default;

Challenge::Challenge(Station startStation, Station destinationStation, Difficulty difficulty) :
        startLine(startStation.getTransfers()[0]), // Set startLine to NULL_TRAIN by default
        startStation(startStation),
        destinationStation(destinationStation),
        difficulty(difficulty) {}


void Challenge::setStartLine(LineName newStartLine) {
    startLine = newStartLine;
}

LineName Challenge::getStartLine() {
    return startLine;
}


void Challenge::setStartStation(Station newStartStation) {
    startStation = newStartStation;
}

Station Challenge::getStartStation() {
    return startStation;
}


void Challenge::setDestinationStation(Station newDestinationStation) {
    destinationStation = newDestinationStation;
}

Station Challenge::getDestinationStation() {
    return destinationStation;
}


Difficulty Challenge::getDifficulty() {
    return difficulty;
}

string Challenge::getDifficultyString() {
    return DifficultyStrings[difficulty];
}

void Challenge::setDifficulty(Difficulty newDifficulty) {
    difficulty = newDifficulty;
}

vector<Challenge> Challenge::getAllChallenges() {
    return allChallenges;
}


void Challenge::initializeAllChallenges() {
    ifstream file("../challenges/challenge_data.csv");
    string header; // Read header (ignore)
    if (file) {
        getline(file, header);
    }

    // Build variables
    string startId, destId, difficultyStr, emptyString;
    char comma = ',';
    Difficulty difficulty;

    while (file && file.peek() != EOF) {
        // read startId
        getline(file, startId, comma);

        // read destId
        getline(file, destId, comma);

        // read difficulty
        file >> difficultyStr;
        getline(file, emptyString);
        if (difficultyStr == "0") {
            difficulty = EASY;
        }
        else if (difficultyStr == "1") {
            difficulty = MEDIUM;
        }
        else if (difficultyStr == "2") {
            difficulty = HARD;
        }
        else if (difficultyStr == "3") {
            difficulty = CUSTOM;
        }

        // Create stations
        Station startStation = Station::getStation(startId);
        Station destStation = Station::getStation(destId);

        // Create and add challenge
        addNewChallenge(Challenge(startStation,destStation, difficulty));
    }

    file.close();
}


void Challenge::addNewChallenge(Challenge newChallenge) {
    allChallenges.emplace_back(newChallenge);
}

void Challenge::writeNewChallenge(Challenge newChallenge) {
    // do stuff
    string startStationId = newChallenge.getStartStation().getId();
    string destStationId = newChallenge.getDestinationStation().getId();
    Difficulty difficulty = newChallenge.getDifficulty();
    char comma = ',';

    ofstream outputFile("../challenges/challenge_data.csv", ios::app); // ::app to keep exising contents

    outputFile << startStationId << comma << destStationId << comma << difficulty << endl;
}



ostream& operator<<(ostream& str, Challenge challenge) {
    const string startStationStr     = challenge.getStartStation().getName();
    const string startStationTrfrStr = challenge.getStartStation().getTransferLinesString();
    const string destiStationStr     = challenge.getDestinationStation().getName();
    const string destiStationTrfrStr = challenge.getDestinationStation().getTransferLinesString();
    const string difficultyStr       = challenge.getDifficultyString();

    str << left << setw(32) << startStationStr;
    str << "  " << setw(22) << left << startStationTrfrStr;

    str << setw(12) << left << "----->" << "   ";

    str << left << setw(32) << destiStationStr;
    str << "  " << setw(22) << left << destiStationTrfrStr;
    str << "  " << setw(10) << left << difficultyStr;

    return str;
}


