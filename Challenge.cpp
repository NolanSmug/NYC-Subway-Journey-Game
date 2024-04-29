
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
    string start_id, dest_id, difficulty_str,emptyString;
    char comma = ',';
    Difficulty difficulty;

    while (file && file.peek() != EOF) {
        // read start_id
        getline(file, start_id, comma);

        // read dest_id
        getline(file, dest_id, comma);

        // read difficulty
        file >> difficulty_str;
        getline(file, emptyString);
        if (difficulty_str == "0") {
            difficulty = EASY;
        }
        else if (difficulty_str == "1") {
            difficulty = MEDIUM;
        }
        else if (difficulty_str == "2") {
            difficulty = HARD;
        }

        // Create stations
        Station start_station = Station::getStation(start_id);
        Station dest_station = Station::getStation(dest_id);

        // Create and add challenge
        addNewChallenge(Challenge(start_station, dest_station, difficulty));
    }

    file.close();
}


void Challenge::addNewChallenge(Challenge newChallenge) {
    allChallenges.emplace_back(newChallenge);
}

void Challenge::wrtieNewChallenge(Challenge newChallenge) {
    // do stuff
}



// overloaded cout operator
ostream& operator<<(ostream& str, Challenge challenge) {
    Station startStation = challenge.getStartStation();
    Station destiStation = challenge.getDestinationStation();

    int minStationNameWidth = 32;
    int minTransferLineWidth = 20;

    str << left << setw(minStationNameWidth) << startStation.getName();
    str << "  " << setw(minTransferLineWidth) << left << startStation.getTransferLinesString();

    str << setw(10) << left << "----->" << "   ";

    str << left << setw(minStationNameWidth) << destiStation.getName();
    str << "  " << setw(minTransferLineWidth) << left << destiStation.getTransferLinesString();

    return str;
}


