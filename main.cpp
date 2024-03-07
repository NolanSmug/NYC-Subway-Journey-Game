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

Direction handleStartingDirection(string &uptownLabel, string &downtownLabel);

bool handleUserInput(Train &train, string &uptownLabel, string &downtownLabel);

bool askUserToTransfer(Train &train);
bool handleTransfer(Train &train, string &uptownLabel, string &downtownLabel);
bool handleAdvanceOneStation(Train &train);
bool handleChangeDirection(Train &train);
bool handleAdvanceMultipleStations(Train &train, string &input);


void handleLastStop(Train &train);

void displayCurrentStationInfo(Train &train, string &uptownLabel, string &downtownLabel);
void printAllStations(vector<Station> stations, string currentStationId, Direction currentDirection);

/*
 * Deprecated:
 *  bool prompt_transfer(Station station);
 *  Station advance_station_from_user(Train &train);
 */

int main() {
    // SET UP STARTING LINE
    SubwayMap subwayMap = SubwayMap();
    LineName startingLine = Line::getRandomLine();
//  startingLine = FOUR_TRAIN; (testing purposes)

    vector<Station> currentStations;
    vector<Station> allStations;

    SubwayMap::createStations(startingLine, currentStations);
    SubwayMap::createStations(NULL_TRAIN, allStations); // NULL_TRAIN returns all the NYC stations

//    printAllStations(currentStations);

    // SET UP STATION OBJECTS
    unsigned int numStations = currentStations.size();
    unsigned int const totalNumStations = allStations.size();

    int startingStation = getRandomStation(numStations);
    int destinationStation = startingStation;

    // make sure destination station != starting stations
    while (allStations[destinationStation].getId() == allStations[startingStation].getId()) {
        destinationStation = getRandomStation(totalNumStations);
    }

    // START TRAIN
    Train train = Train(startingLine, UPTOWN, currentStations, false, 10);
    train.setCurrentStation(startingStation);

    string uptownLabel = Train::getTextForDirectionEnum(UPTOWN,train.getLine());
    string downtownLabel = Train::getTextForDirectionEnum(DOWNTOWN,train.getLine());

    displayCurrentStationInfo(train, uptownLabel, downtownLabel);
    cout << "Destination Station:\n" << allStations[destinationStation];

    train.setDirection(handleStartingDirection(uptownLabel, downtownLabel)); // ask user for a direction they want to start going

    // GAME LOOP
    while (train.getCurrentStation().getId() != allStations[destinationStation].getId()) {
        displayCurrentStationInfo(train, uptownLabel, downtownLabel);

        unsigned int currentStationIndex = train.getCurrentStationIndex();
        unsigned int lastStationIndex = train.getScheduledStops().size() - 1;
        bool atLastStop = (currentStationIndex == 0                && train.getDirection() == DOWNTOWN) ||
                          (currentStationIndex == lastStationIndex && train.getDirection() == UPTOWN);
        if (atLastStop) {
            handleLastStop(train);
        }

        bool validInput = false;
        while (!validInput) {
            validInput = handleUserInput(train, uptownLabel, downtownLabel);
        }
    }

    bool test = train.getCurrentStation().getTransfers() == allStations[destinationStation].getTransfers();

    // GAME FINISHED
    if (train.getCurrentStation().getName() == allStations[destinationStation].getName() &&
        train.getCurrentStation().getTransfers() == allStations[destinationStation].getTransfers()) {
        cout << "\nYour current Station:\n" << train.getCurrentStation();
        cout << "YOU WIN" << endl;
    }

    return 0;
}



bool handleUserInput(Train &train, string &uptownLabel, string &downtownLabel) {
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
        return handleTransfer(train, uptownLabel, downtownLabel);
    }
    else if (tolower(input[0]) == 'c' && input.length() == 1) {
        return handleChangeDirection(train);
    }
    else {
        return handleAdvanceMultipleStations(train, input);
    }
}

void displayCurrentStationInfo(Train &train, string &uptownLabel, string &downtownLabel) {
    Station currentStation = train.getCurrentStation();
    Direction currentDirection = train.getDirection();

    cout << "\nYour Current Line:\n" << (currentDirection == DOWNTOWN ? downtownLabel + " " + Line::getTextForEnum(train.getLine()) + " Train ↓" : uptownLabel + " "  + Line::getTextForEnum(train.getLine()) + " Train ↑") << endl;
    cout << "\nYour current Station:\n" << currentStation;
}

bool handleAdvanceOneStation(Train &train) {
    train.advanceStation();
    return true;
}

bool handleTransfer(Train &train, string &uptownLabel, string &downtownLabel) {
    askUserToTransfer(train);
    train.setDirection(handleStartingDirection(uptownLabel, downtownLabel));

    uptownLabel = Train::getTextForDirectionEnum(UPTOWN, train.getLine());
    downtownLabel = Train::getTextForDirectionEnum(DOWNTOWN, train.getLine());

    return true;
}

bool handleChangeDirection(Train &train) {
    train.setDirection(train.getDirection() == DOWNTOWN ? UPTOWN : DOWNTOWN);
    string trackLabel = Train::getTextForDirectionEnum(train.getDirection(), train.getLine());
    cout << "You switched to the " << trackLabel << " platform." << endl;

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


Direction handleStartingDirection(string &uptownLabel, string &downtownLabel) {
    bool valid = false;
    string input = " ";

    while (!valid) {
        cout << "Would you like to enter traveling |" << uptownLabel << " ↑| (u), or |"<< downtownLabel << " ↓| (d) ? ";
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
            for (LineName line : currentStation.getTransfers()) {
                cout << Line::getTextForEnum(line) << " ";
            }
            cout << endl;
            alreadyListedTransfers = true;
        }
        else if (tolower(input[0]) == 'e') {
            valid = false;
            break;
        }
        else {
            cout << "Invalid input. ";
        }
    }

    return valid;
}

void printAllStations(vector<Station> stations, string currentStationId, Direction currentDirection) {
    int length = stations.size();
    int currentStationIndex = -1;

    // Find the index of the current station
    for (int i = 0; i < length; i++) {
        if (stations[i].getId() == currentStationId) {
            currentStationIndex = i;
            break;
        }
    }

    cout << "---------------------------------" << endl;
    if (currentDirection == UPTOWN) {
        cout << "↑" << endl;
        for (int i = currentStationIndex; i < length; i++) {
            int stopsAway = i - currentStationIndex;
            string stopsAwayText = stopsAway == 0 ? "" : (stopsAway == 1 ? "(Next Stop)" : "(" + to_string(stopsAway) + " stops away)");

            if (stations[i].getId() == currentStationId) {
                cout << setw(30) << left << stations[i].getName() << "  **  Current Station  **" << endl;
                cout << "|" << endl;
            } else {
                cout << setw(35) << left << stations[i].getName() << stopsAwayText << endl;
                cout << "|" << endl;
            }
        }
    } else {
        cout << "↓" << endl;
        for (int i = currentStationIndex; i >= 0; i--) {
            int stopsAway = currentStationIndex - i;
            string stopsAwayText = stopsAway == 0 ? "" : (stopsAway == 1 ? "(Next Stop)" : "(" + to_string(stopsAway) + " stops away)");

            if (stations[i].getId() == currentStationId) {
                cout << setw(30) << left << stations[i].getName() << "  **  Current Station  **" << endl;
                cout << "|" << endl;
            } else {
                cout << setw(35) << left << stations[i].getName() << stopsAwayText << endl;
                cout << "|" << endl;
            }
        }
    }
    cout << "---------------------------------" << endl;
}



/*

* DEPRECATED *

Station advance_station_from_user(Train &train) {
    bool valid = false;
    int input_int = 0;

    while (!valid) {
        cout << "How many stops would you like to advance? (enter nothing for 1) ";
        string input_string;
        getline(cin, input_string);

        if (input_string.empty()) { // advance one Station
            if (train.advanceStation()) {
                valid = true;
            } else {
                cout << "Invalid input. ";
            }
            continue;
        }

        stringstream ss(input_string);
        bool valid_int = ss >> input_int && to_string(input_int).length() == input_string.length();

        if (valid_int && train.advanceStation(input_int)) { // advance input_int Stations
            valid = true;
        }
        else {
            cout << "Invalid input. ";
        }
    }

    cout << "\nCurrent Station:\n";
    return train.getCurrentStation();
}

bool prompt_transfer(Station station) {
        while (true) {
            cout << "Transfers are available (type 't' to list them). Enter the transfer line or 't': ";

            string input;
            getline(cin, input);

            if (input.length() > 1) {
                cout << "Invalid input. ";
            }
            else if (tolower(input[0]) == 't') {
                for (LineName line : station.getTransfers()) {
                    cout << Line::getTextForEnum(line) << " ";
                }
                cout << endl;
            }
            else if (station.hasTransferLine(input)) {
                return true;
            }
            else {
                cout << "Invalid input. ";
            }
        }

    return false; // no transfers at the station
}
*/
