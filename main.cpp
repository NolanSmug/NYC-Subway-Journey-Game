#include "Station.h"
#include "SubwayMap.h"
#include "Train.h"
#include "Line.h"
#include "sstream"
#include "random"
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

using namespace std;

int getRandomStation(unsigned int numStations);

Direction handleNewDirection(Train &train);

bool handleUserInput(Train &train);

bool askUserToTransfer(Train &train);
bool handleTransfer(Train &train);
bool handleAdvanceOneStation(Train &train);
bool handleChangeDirection(Train &train);
bool handleAdvanceMultipleStations(Train &train, string &input);

void handleLastStop(Train &train);

void displayCurrentStationInfo(Train &train);
void printAllStations(vector<Station> stations, string currentStationId, Direction currentDirection);
void printTransferLines(vector<LineName> transfers);

void handleStartingLine(Train &train);

int main() {
    // SET UP STARTING LINE
    SubwayMap subwayMap = SubwayMap();
    LineName startingLine = Line::getRandomLine();
//  startingLine = FOUR_TRAIN; (testing purposes)

    vector<Station> currentStations;
    vector<Station> allStations;

    SubwayMap::createStations(startingLine, currentStations);
    SubwayMap::createStations(NULL_TRAIN, allStations); // NULL_TRAIN returns all the NYC stations

    unsigned int numStations = currentStations.size();
    unsigned int const totalNumStations = allStations.size();

    int startingStation = getRandomStation(numStations);
    int destinationStation = startingStation;

    // make sure destination station != starting stations
    while (allStations[destinationStation].getId() == allStations[startingStation].getId()) {
        destinationStation = getRandomStation(totalNumStations);
    }

    // START TRAIN
    Train train = Train(startingLine, NULL_DIRECTION, currentStations, false, 10);
    train.setCurrentStation(startingStation);

    displayCurrentStationInfo(train);
    cout << "Destination Station:\n" << allStations[destinationStation];

    handleStartingLine(train);


    train.setDirection(handleNewDirection(train)); // ask user for a direction they want to start going

    // GAME LOOP
    while (train.getCurrentStation().getId() != allStations[destinationStation].getId()) {
        displayCurrentStationInfo(train);

        unsigned int currentStationIndex = train.getCurrentStationIndex();
        unsigned int lastStationIndex = train.getScheduledStops().size() - 1;
        bool atLastStop = (currentStationIndex == 0                && train.getDirection() == DOWNTOWN) ||
                          (currentStationIndex == lastStationIndex && train.getDirection() == UPTOWN);
        if (atLastStop) {
            handleLastStop(train);
        }

        bool validInput = false;
        while (!validInput) {
            validInput = handleUserInput(train);
        }
    }

    // GAME FINISHED
    if (train.getCurrentStation().getName() == allStations[destinationStation].getName() &&
        train.getCurrentStation().getTransfers() == allStations[destinationStation].getTransfers()) {
        cout << "\nYour current Station:\n" << train.getCurrentStation();
        cout << "YOU WIN" << endl;
    }

    return 0;
}

bool handleUserInput(Train &train) {
    string input;
    cout << "Enter 't' to transfer | 'c' to change direction | a number to advance that many stations (nothing advances 1 station)  ";
    getline(cin, input);

    if (input.empty()) {
        return handleAdvanceOneStation(train);
    }
    else if (input[0] == '0' && input.length() == 1) {
        printAllStations(train.getScheduledStops(), train.getCurrentStation().getId(),train.getDirection());
    }
    else if (tolower(input[0]) == 't' && input.length() == 1) {
        return handleTransfer(train);
    }
    else if (tolower(input[0]) == 'c' && input.length() == 1) {
        return handleChangeDirection(train);
    }
    else {
        return handleAdvanceMultipleStations(train, input);
    }
    return false;
}

void displayCurrentStationInfo(Train &train) {
    Station currentStation = train.getCurrentStation();
    Direction currentDirection = train.getDirection();

    if (currentDirection == NULL_DIRECTION) {
        cout << "\nYour Current Line:\n" << Line::getTextForEnum(train.getLine()) + " Train ↕" << endl;
    }
    else {
        cout << "\nYour Current Line:\n" << (currentDirection == DOWNTOWN ? train.getDowntownLabel() + " " + Line::getTextForEnum(train.getLine()) + " Train ↓" : train.getUptownLabel() + " "  + Line::getTextForEnum(train.getLine()) + " Train ↑") << endl;
    }

    cout << "\nYour current Station:\n" << currentStation;
}

bool handleAdvanceOneStation(Train &train) {
    train.advanceStation();
    return true;
}

bool handleTransfer(Train &train) {
    if (askUserToTransfer(train)) {
        train.setDirection(handleNewDirection(train));

        train.setUptownLabel(Train::getTextForDirectionEnum(UPTOWN, train.getLine()));
        train.setDowntownLabel(Train::getTextForDirectionEnum(DOWNTOWN, train.getLine()));
    }

    return true;
}

bool handleChangeDirection(Train &train) {
    train.setDirection(train.getDirection() == DOWNTOWN ? UPTOWN : DOWNTOWN);
    string trackLabel = Train::getTextForDirectionEnum(train.getDirection(), train.getLine());
    cout << "\nYou switched to the " << trackLabel << " platform." << endl;

    return true;
}

bool handleAdvanceMultipleStations(Train &train, string &input) {
    int stationsToAdvance;

    istringstream inputStringStream(input);
    if (inputStringStream >> stationsToAdvance && train.advanceStation(stationsToAdvance)) {
        return true;
    }

    return false;
}

void handleLastStop(Train &train) {
    cout << "This is the last stop on this train. Everyone please leave the train, thank you for riding with MTA New York City Transit" << endl;
    // switch direction
    train.setDirection(train.getDirection() == DOWNTOWN ? UPTOWN : DOWNTOWN);
    string trackLabel = Train::getTextForDirectionEnum(train.getDirection(), train.getLine());

    cout << "You switched to the " << trackLabel << " platform." << endl;
    this_thread::sleep_for(chrono::seconds(2)); // wait so user realizes
}

int getRandomStation(unsigned int numStations) {
    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_int_distribution<> distribution(0, numStations - 1);
    return distribution(generator);
}

Direction handleNewDirection(Train &train) {
    bool valid = false;
    string input = " ";

    while (!valid) {
        cout << "Would you like to enter traveling |" << train.getUptownLabel() << " ↑| (u), or |"<< train.getDowntownLabel() << " ↓| (d) ? ";
        getline(cin, input);

        uint length = input.length();

        if (length == 0) {
            cout << "No input. ";
        }
        else if ((tolower(input[0]) == 'd' || tolower(input[0]) == 'u') &&length == 1) {
            valid = true;
        }
        else {
            cout << "Invalid input. ";
        }
    }

    return tolower(input[0]) == 'd' ? DOWNTOWN : UPTOWN;
}

bool askUserToTransfer(Train &train) {
    Station currentStation = train.getCurrentStation();
    string input;

    bool valid = false;
    bool alreadyListedTransfers = false;
    while (!valid) {
        if (alreadyListedTransfers) {
            cout << "Which line would you like to transfer to? (e to exit) ";
        }
        else {
            cout << "Which line would you like to transfer to? (t to list them) | (e to exit) ";
        }
        getline(cin, input);

        if (currentStation.hasTransferLine(input)) {
            valid = train.transferToLine(Line::stringToLineEnum(input), currentStation);
        }
        else if (tolower(input[0]) == 't') {
            printTransferLines(train.getCurrentStation().getTransfers());
            cout << endl;
            alreadyListedTransfers = true;
        }
        else if (tolower(input[0]) == 'e') {
            return false;
        }
        else {
            cout << "Invalid input. ";
        }
    }

    return valid;
}

void handleStartingLine(Train &train) {
    bool validLine = false;

    while (!validLine) {
        cout << "Choose a train line to wait for at " << train.getCurrentStation().getName() << " (";

        printTransferLines(train.getCurrentStation().getTransfers());

        cout << "): ";

        string lineChoice;
        getline(cin, lineChoice);

        if (train.transferToLine(Line::stringToLineEnum(lineChoice),train.getCurrentStation())) {
            validLine = true;
        }
        else {
            cout << "Invalid line choice. Try again." << endl;
        }
    }
}

void printTransferLines(vector<LineName> transfers) {
    unsigned int numTransfers = transfers.size();

    for (int i = 0; i < numTransfers; ++i) {
        cout << Line::getTextForEnum(transfers[i]);
        if (i != numTransfers - 1) { // If it's not the last line, print a space
            cout << " ";
        }
    }
}

void printAllStations(vector<Station> stations, string currentStationId, Direction currentDirection) {
    unsigned int numStations = stations.size();
    int currentStationIndex = -1;

    // Find the index of the current station
    for (int i = 0; i < numStations; i++) {
        if (stations[i].getId() == currentStationId) {
            currentStationIndex = i;
            break;
        }
    }

    cout << "------------------------------------------------------------------" << endl;
    if (currentDirection == UPTOWN) {
        for (int i = numStations - 1; i >= currentStationIndex; i--) {
            int stopsAway = abs(i - currentStationIndex);
            string stopsAwayText = stopsAway == 0 ? "" : (stopsAway == 1 ? "(Next Stop)" : "(" + to_string(stopsAway) + " stops away)");

            if (stations[i].getId() == currentStationId) {
                cout << setw(30) << left << stations[i].getName() << "  **  Current Station  **" << endl;
                cout << "    |" << endl;
            } else {
                cout << setw(35) << left << stations[i].getName() << stopsAwayText << endl;
                cout << "    |" << endl;
            }
        }
        cout << "    ↑" << endl;
    }
    else { // DOWNTOWN
        cout << "    ↓" << endl;
        for (int i = currentStationIndex; i < numStations; i--) {
            int stopsAway = abs(i - currentStationIndex);
            string stopsAwayText = stopsAway == 0 ? "" : (stopsAway == 1 ? "(Next Stop)" : "(" + to_string(stopsAway) + " stops away)");

            if (stations[i].getId() == currentStationId) {
                cout << setw(30) << left << stations[i].getName() << " **  Current Station  **" << endl;
                cout << "    |" << endl;
            }
            else {
                cout << setw(35) << left << stations[i].getName() << stopsAwayText << endl;
                cout << "    |" << endl;
            }
        }
    }
    cout << "------------------------------------------------------------------" << endl;
}
