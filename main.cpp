#include "Station.h"
#include "SubwayMap.h"
#include "Train.h"
#include "Line.h"
#include "sstream"
#include "random"
#include <iostream>

using namespace std;

Direction get_direction_from_user();
bool prompt_transfer(Station station);
bool ask_user_to_transfer(Train &train);
Station advance_station_from_user(Train &train);
int get_random_station(unsigned int numStations);
void print_all_stations(vector<Station> stations);

int main() {
    SubwayMap subwayMap = SubwayMap();
    vector<Station> stations;
    subwayMap.createAllStations("../csv/one_train_stations.csv", stations);

    print_all_stations(stations);

    // set up starting and ending stations
    unsigned int numStations = stations.size();
    int startingStation = get_random_station(numStations);
    int destinationStation = startingStation;

    // make sure destination station is at least 4 stops away
    while (destinationStation == startingStation && abs(startingStation - destinationStation) <= 4) {
        destinationStation = get_random_station(numStations);
    }

    // START GAME
    Train oneLine = Train(ONE_TRAIN, BRONXBOUND, stations, false, 10);
    // startingStation = 8; // testing purposes
    oneLine.setCurrentStation(startingStation);
    cout << "Your Current Line:\n" << Train::getTextForEnum(oneLine.getDirection()) << " " << Line::getTextForEnum(oneLine.getName()) << " Train" << endl;
    cout << "\nYour current Station:\n" << oneLine.getCurrentStation();
    cout << "Destination Station:\n" << stations[destinationStation];

    oneLine.setDirection(get_direction_from_user()); // ask user for a direction they want to start going

    // game loop
    while (oneLine.getCurrentStation().getName() != stations[destinationStation].getName()) {
        Station currentStation = oneLine.getCurrentStation();
        Direction currentDirection = oneLine.getDirection();

        if (prompt_transfer(oneLine.getCurrentStation())) {
            ask_user_to_transfer(oneLine);
            oneLine.setDirection(get_direction_from_user());
            print_all_stations(oneLine.getScheduledStops());
            cout << "Your Current Line:\n" << Train::getTextForEnum(currentDirection) << " "
                 << Line::getTextForEnum(oneLine.getName()) << " Train" << endl;
            cout << "\nYour current Station:\n" << currentStation;
        } else {
            cout << advance_station_from_user(oneLine);
        }
    }

// CURRENTLY REMOVED (after the transfer logic was added)
        // check to see if the user passed the destination station, in which case they lose the game (for now)
//        const Direction direction = oneLine.getDirection();
//        const int currentIndex = oneLine.getCurrentStationIndex();
//        if ((direction == MANHATTANBOUND && currentIndex < destinationStation) ||
//            (direction == BRONXBOUND && currentIndex > destinationStation)) {
//            break;
//        }

    // game over stuff
    if (oneLine.getCurrentStation().getName() == stations[destinationStation].getName()) {
        cout << "YOU WIN" << endl;
    }
    else {
        cout << "UH OH, YOU MISSED/PASSED THE STATION!\nGAME OVER" << endl;
    }

    return 0;
}

int get_random_station(unsigned int numStations) {
    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_int_distribution<> distribution(0, numStations - 1);
    return distribution(generator);
}

Direction get_direction_from_user() {
    bool valid = false;
    string input = " ";

    while (!valid) {
        cout << "Would you like to enter traveling Uptown (u) or Downtown (d)? ";
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

    return tolower(input[0]) == 'd' ? MANHATTANBOUND : BRONXBOUND; // TODO: don't forget this needs to be updated soon
}

bool prompt_transfer(Station station) {
    bool alreadyListedTransfers = false;
    if (station.getTransfers().size() > 1) {
        while (true) {
            if (alreadyListedTransfers) {
                cout << "Transfers are available. Would you like to transfer? (y/n) ";
            }
            else {
                cout << "Transfers are available (type 't' to list them). Would you like to transfer? (y/n) ";
            }

            string input;
            getline(cin, input);

            if (input.length() > 1) {
                cout << "Invalid input. ";
            }
            else if (tolower(input[0]) == 'y') {
                return true;
            }
            else if (tolower(input[0]) == 'n') {
                return false;
            }
            else if (tolower(input[0]) == 't') {
                for (LineName line : station.getTransfers()) {
                    cout << line << " ";
                }
                cout << endl;
                alreadyListedTransfers = true;
            }
            else {
                cout << "Invalid input. ";
            }
        }
    }

    return false; // no transfers at the station
}

bool ask_user_to_transfer(Train &train) {
    Station currentStation = train.getCurrentStation();
    string input;

    bool valid = false;
    while (!valid) {
        cout << "Which line would you like to transfer to? (e to exit) ";
        getline(cin, input);

        if (currentStation.hasTransferLine(input)) {
            valid = train.transferToLine(Line::stringToLineEnum(input), currentStation);
        }
        else if (tolower(input[0]) == 'e') {
            valid = false;
        }
        else {
            cout << "Invalid input. ";
        }
    }

    return valid;
}


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
