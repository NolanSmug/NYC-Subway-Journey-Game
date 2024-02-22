#include "Station.h"
#include "SubwayMap.h"
#include "Train.h"
#include "sstream"
#include "random"
#include <iostream>

using namespace std;

Direction get_direction_from_user();
Station advance_station_from_user(Train &train);
int get_random_station(unsigned int numStations);

int main() {
    SubwayMap subwayMap = SubwayMap();
    vector<Station> stations;
    subwayMap.createAllStations("../csv/one_train_stations.csv", stations);

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
    oneLine.setCurrentStation(startingStation);
    cout << "Your current Station:\n" << oneLine.getCurrentStation();
    cout << "Destination Station:\n" << stations[destinationStation];

//    oneLine.transferToLine(TWO_TRAIN,stations[startingStation]);

    oneLine.setDirection(get_direction_from_user()); // ask user for a direction they want to start going

    // game loop
    while (oneLine.getCurrentStation().getName() != stations[destinationStation].getName()) {
        cout << advance_station_from_user(oneLine); // ask user how many stations they'd like to advance and advance

        // check to see if user passed the destination station, in which case they lose the game (for now)
        if (oneLine.getDirection() == MANHATTANBOUND &&
            oneLine.getCurrentStationIndex() < destinationStation) {
            break;
        }
        else if (oneLine.getDirection() == BRONXBOUND &&
                 oneLine.getCurrentStationIndex() > destinationStation) {
            break;
        }
    }

    // game over stuff
    if (oneLine.getCurrentStation().getName() == stations[destinationStation].getName()) {
        cout << "YOU WIN" << endl;
    }
    else {
        cout << "UH OH, YOU MISSED/PASSED THE STATION!\nGAME OVER" << endl;
    }
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

Station advance_station_from_user(Train &train) {
    bool valid = false;
    int input_int = 0;

    while (!valid) {
        cout << "How many stops would you like to advance? (enter nothing for 1) ";
        string input_string;
        getline(cin, input_string);

        if (input_string.length() == 0) {
            if (train.advanceStation()) {
                valid = true;
            } else {
                cout << "Invalid input. ";
            }
            continue;
        }

        stringstream ss(input_string);
        bool valid_int = ss >> input_int && to_string(input_int).length() == input_string.length();

        if (valid_int && train.advanceStation(input_int)) {
            valid = true;
        }
        else {
            cout << "Invalid input. ";
        }
    }

    cout << "\nCurrent Station:\n";
    return train.getCurrentStation();
}
