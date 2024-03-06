#include "Station.h"
#include "SubwayMap.h"
#include "Train.h"
#include "Line.h"
#include "sstream"
#include "random"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void print_all_stations(vector<Station> stations);
int get_random_station(unsigned int numStations);

Direction get_direction_from_user(string uptownLabel, string downtownLabel);
bool ask_user_to_transfer(Train &train);

void displayCurrentStationInfo(Train& train, const string& uptownLabel, const string& downtownLabel);
void handleLastStop(Train& train, const int destinationStation, const vector<Station>& allStations);
bool handleUserInput(Train& train, string& uptownLabel, string& downtownLabel);

/*
 * Deprecated:
 *  bool prompt_transfer(Station station);
 *  Station advance_station_from_user(Train &train);
 */

int main() {
    // set up the Line the user starts in
    SubwayMap subwayMap = SubwayMap();
    LineName startingLine = Line::getRandomLine();

    vector<Station> currentStations;
    vector<Station> allStations;

    subwayMap.createStations(startingLine, currentStations);
    subwayMap.createStations(NULL_TRAIN, allStations); // NULL_TRAIN returns all the NYC stations

//    print_all_stations(currentStations);

    // set up starting and ending stations
    unsigned int numStations = currentStations.size();
    unsigned int const totalNumStations = allStations.size();

    int startingStation = get_random_station(numStations);
    int destinationStation = startingStation;

    // make sure destination station is at least 4 stops away
    while (destinationStation == startingStation && abs(startingStation - destinationStation) <= 4) {
        destinationStation = get_random_station(totalNumStations);
    }

    // START GAME
    Train train = Train(startingLine, UPTOWN, currentStations, false, 10);
    // startingStation = 8; // testing purposes
    train.setCurrentStation(startingStation);

    string uptownLabel = Train::getTextForDirectionEnum(UPTOWN,train.getLine());
    string downtownLabel = Train::getTextForDirectionEnum(DOWNTOWN,train.getLine());

    cout << "Your Current Line:\n" <<  Line::getTextForEnum(train.getLine()) << " Train\n" << "↑ " << uptownLabel << "\n↓ " << downtownLabel << endl;
    cout << "\nYour current Station:\n" << train.getCurrentStation();
    cout << "Destination Station:\n" << allStations[destinationStation];

    train.setDirection(get_direction_from_user(uptownLabel, downtownLabel)); // ask user for a direction they want to start going

    // game loop
    while (train.getCurrentStation().getName() != allStations[destinationStation].getName()) {
        displayCurrentStationInfo(train, uptownLabel, downtownLabel);

        int currentStationIndex = train.getCurrentStationIndex();
        bool atLastStop = (currentStationIndex == 0 && train.getDirection() == DOWNTOWN) ||
                          (currentStationIndex == train.getScheduledStops().size() - 1 && train.getDirection() == UPTOWN);
        if (atLastStop) {
            handleLastStop(train, destinationStation, allStations);
        }

        bool validInput;
        do {
            validInput = handleUserInput(train, uptownLabel, downtownLabel);


        } while (!validInput);
    }

    // game over stuff
    if (train.getCurrentStation().getId() == allStations[destinationStation].getId()) {
        cout << "\nYour current Station:\n" << train.getCurrentStation();
        cout << "YOU WIN" << endl;
    }

    return 0;
}

void displayCurrentStationInfo(Train& train, const string& uptownLabel, const string& downtownLabel) {
    Station currentStation = train.getCurrentStation();
    Direction currentDirection = train.getDirection();

    cout << "\nYour Current Line:\n" << (currentDirection == DOWNTOWN ? downtownLabel + " " + Line::getTextForEnum(train.getLine()) + " Train ↓" : uptownLabel + " "  + Line::getTextForEnum(train.getLine()) + " Train ↑") << endl;
    cout << "\nYour current Station:\n" << currentStation;
}

bool handleUserInput(Train& train, string &uptownLabel, string &downtownLabel) {
    Station currentStation = train.getCurrentStation();
    Direction currentDirection = train.getDirection();

    string input;
    cout << "Enter 't' to transfer | 'c' to change direction | a number to advance that many stations (nothing advances 1 station)  ";
    getline(cin, input);

    // user wants to advance 1 station
    if (input.empty()) {
        train.advanceStation();
        return true;
    }
        // user wants to transfer
    else if (tolower(input[0]) == 't' && input.length() == 1) {
        ask_user_to_transfer(train);
        train.setDirection(get_direction_from_user(uptownLabel, downtownLabel));

        uptownLabel = Train::getTextForDirectionEnum(UPTOWN, train.getLine());
        downtownLabel = Train::getTextForDirectionEnum(DOWNTOWN, train.getLine());

        return true;
    }
        // user wants to change direction
    else if (tolower(input[0]) == 'c' && input.length() == 1) {
        train.setDirection(currentDirection == DOWNTOWN ? UPTOWN : DOWNTOWN);
        string trackLabel = Train::getTextForDirectionEnum(currentDirection, train.getLine());
        cout << "You switched to the " << trackLabel << " platform." << endl;
        return true;
    }
        // user wants to advance > 1 station
    else {
        int numStationsInput;
        istringstream iss(input);
        if (iss >> numStationsInput && train.advanceStation(numStationsInput)) {
            // Advanced numStations stations
            return true;
        }
        else {
            // Invalid input. ask again
            return false;
        }
    }
}

void handleLastStop(Train& train, const int destinationStation, const vector<Station>& allStations) {
    Station currentStation = train.getCurrentStation();
    Direction currentDirection = train.getDirection();

    if (currentStation.getName() != allStations[destinationStation].getName() && train.getLine() != S_TRAIN) {
        cout << "This is the last stop on this train. Please get off." << endl;

        train.setDirection(currentDirection == DOWNTOWN ? UPTOWN : DOWNTOWN);
        string trackLabel = Train::getTextForDirectionEnum(currentDirection, train.getLine());

        cout << "You switched to the " << trackLabel << " platform." << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
}


int get_random_station(unsigned int numStations) {
    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_int_distribution<> distribution(0, numStations - 1);
    return distribution(generator);
}


Direction get_direction_from_user(string uptownLabel, string downtownLabel) {
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




bool ask_user_to_transfer(Train &train) {
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



void print_all_stations(vector<Station> stations) {
    unsigned int length = stations.size();

    for (int i = 0; i < length; i++) {
        if (i == length - 1) {
            cout << stations[i].getName() << endl;
        }
        else {
            cout << stations[i].getName() << "\n   |\n";
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
