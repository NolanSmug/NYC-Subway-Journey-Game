#include "Station.h"
#include "SubwayMap.h"
#include "Train.h"
#include "Line.h"
#include "Challenge.h"
#include "sstream"
#include "random"
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

using namespace std;

int getRandomStation(unsigned int numStations);

bool handleUserInput(Train &train, const Station &destinationStation);

bool askUserToTransfer(Train &train);
bool handleTransfer(Train &train);

bool handleAdvanceOneStation(Train &train);
bool handleAdvanceMultipleStations(Train &train, string &input);

bool handleChangeDirection(Train &train);
Direction handleNewDirection(Train &train);

void handleStartingLine(Train &train);
void handleLastStop(Train &train);

void displayCurrentStationInfo(Train &train);

void printAllStations(Train &train);
void printTransferLines(vector<LineName> transfers);



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
    Train train = Train(startingLine, NULL_DIRECTION, currentStations, false,10);
    train.setCurrentStation(startingStation);

    displayCurrentStationInfo(train);
    cout << "Destination Station:\n" << allStations[destinationStation];

    if (train.getCurrentStation().hasTransferLine()) {
        handleStartingLine(train);
    }

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
            validInput = handleUserInput(train, allStations[destinationStation]);
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

// METHODS
bool handleUserInput(Train &train, const Station &destinationStation) {

    string input;
    if (train.getCurrentStation().hasTransferLine()) {
        cout << "Options:\n";
        cout << " - Enter a number to advance that many stations (empty advances 1 station)\n";
        cout << " - Enter 't' to transfer\n";
        cout << " - Enter 'c' to change direction\n";
        cout << " - Enter 'd' to display your Destination Station\n";
    }
    else {
        cout << "Options:\n";
        cout << " - Enter a number to advance that many stations (empty advances 1 station)\n";
        cout << " - Enter 'c' to change direction\n";
        cout << " - Enter 'd' to display your Destination Station\n";
    }

    getline(cin, input);

    if (input.empty()) {
        return handleAdvanceOneStation(train);
    }
    else if (tolower(input[0]) == 't' && input.length() == 1) {
        return handleTransfer(train);
    }
    else if (tolower(input[0]) == 'c' && input.length() == 1) {
        return handleChangeDirection(train);
    }
    else if (tolower(input[0]) == 'd' && input.length() == 1) {
        cout << "Destination Station:\n" << destinationStation;
    }
    else if (input[0] == '0' && input.length() == 1) {
        printAllStations(train);
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
        // do nothing
    }
    else {
        cout << "\nYour Current Line:\n";
        cout << (currentDirection == DOWNTOWN ? // if(?) = downtown, else(:) = uptown
                 train.getDowntownLabel() + " " + Line::getTextForEnum(train.getLine()) + " Train ↓" :
                 train.getUptownLabel() + " "  + Line::getTextForEnum(train.getLine()) + " Train ↑");
        cout << endl;
    }

    cout << "\nYour current Station:\n" << currentStation;
}

bool handleAdvanceOneStation(Train &train) {
    if (train.advanceStation()) {
        return true;
    }

    return false;
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
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, numStations - 1);

    return distribution(generator);
}

Direction handleNewDirection(Train &train) {
    bool valid = false;
    string input = " ";

    char uptownLabelValidChar = tolower(train.getUptownLabel()[0]);
    char downtownLabelValidChar = tolower(train.getDowntownLabel()[0]);

    if (uptownLabelValidChar == downtownLabelValidChar) {
        downtownLabelValidChar = train.getDowntownLabel()[4];
    }

    while (!valid) {
        cout << "Would you like to enter traveling |"
             << train.getUptownLabel()   << " ↑| (" << uptownLabelValidChar << "), or |"
             << train.getDowntownLabel() << " ↓| (" << downtownLabelValidChar << ") ";
        getline(cin, input);

        uint length = input.length();

        if (length == 0) {
            cout << "No input. ";
        }
        else if ((tolower(input[0]) == uptownLabelValidChar || tolower(input[0]) == downtownLabelValidChar) && length == 1) {
            valid = true;
        }
        else {
            cout << "Invalid input. ";
        }
    }

    return tolower(input[0]) == downtownLabelValidChar ? DOWNTOWN : UPTOWN; // return requested direction as an enum
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

void printAllStations(Train &train) {
    string currentStationID = train.getCurrentStation().getId();
    vector<Station> stations =  train.getScheduledStops();
    Direction currentDirection = train.getDirection();
    int length = train.getScheduledStops().size();
    int currentStationIndex = train.getCurrentStationIndex();


    cout << "------------------------------------------------------------------" << endl;
    if (currentDirection == UPTOWN) {
        for (int i = length - 1; i >= currentStationIndex; i--) {
            int stopsAway = abs(i - currentStationIndex);
            string stopsAwayText = stopsAway == 0 ? "" : (stopsAway == 1 ? "(Next Stop)" : "(" + to_string(stopsAway) + " stops away)");

            if (stations[i].getId() == currentStationID) {
                cout << setw(30) << left << stations[i].getName() << "  **  Current Station  **" << endl;
                cout << "    |" << endl;
            }
            else {
                cout << setw(35) << left << stations[i].getName() << stopsAwayText << endl;
                cout << "    |" << endl;
            }
        }
        cout << "    ↑" << endl;
    }
    else { // DOWNTOWN
        cout << "    ↓" << endl;
        for (int i = train.getCurrentStationIndex(); i >= 0; i--) {
            int stopsAway = abs(train.getCurrentStationIndex() - i);
            string stopsAwayText = stopsAway == 0 ? "" : (stopsAway == 1 ? "(Next Stop)" : "(" + to_string(stopsAway) + " stops away)");

            if (stations[i].getId() == currentStationID) {
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

void selectChallenge(Train &train, const vector<Station> &allStations) {


}