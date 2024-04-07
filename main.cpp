#include "Station.h"
#include "SubwayMap.h"
#include "Train.h"
#include "Line.h"
#include "Challenge.h"
#include "JourneyManager.h"
#include "sstream"
#include "random"
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <cstdlib>

struct GameState {
    LineName startingLine;
    Station startingStation;
    Station destinationStation;
    vector<Station> currentStations;
    bool isFirstTurn;

    void resetGameState(JourneyManager& journeyManager) { // if user wants to re-shuffle their stations
        startingStation = journeyManager.getRandomStation();
        destinationStation = startingStation;

        while (startingStation == destinationStation) {
            destinationStation = journeyManager.getRandomStation();
        }

        startingLine = startingStation.getTransfers()[0];
        SubwayMap::createStations(startingLine, currentStations);

        isFirstTurn = true;
    }
};

void initializeTrain(Train& train, GameState& gameState);
void selectChallenge(JourneyManager& journeyManager, GameState& gameState);

Direction handleNewDirection(Train &train);
void handleStartingLine(Train &train);
bool handleUserInput(Train &train, const Station &destinationStation, GameState& gameState, JourneyManager& journeyManager);

bool handleAdvanceOneStation(Train &train);
bool handleAdvanceMultipleStations(Train &train, string &input);
bool handleChangeDirection(Train &train);
bool handleTransfer(Train &train);

bool askUserToTransfer(Train &train);

void printCurrentStationInfo(Train &train);
void printAllStations(Train &train);

void handleLastStop(Train &train);

int getRandomStation(unsigned int numStations);

bool challengeModeFlag = false; // set to false to skip first input
bool easyModeFlag = true;      // set to true to print the current lines' scheduled stops after each turn

int main() {
    // SET UP JOURNEY MANAGER
    JourneyManager journeyManager = JourneyManager();

    GameState gameState; // holds data for the current game's parameters
    gameState.resetGameState(journeyManager);

    // SELECT GAME MODE
    if (challengeModeFlag) {
        string gameMode;
        cout << "Would you like to play Normal Mode (any key) or Challenge Mode (c)? ";
        getline(cin, gameMode);

        if (tolower(gameMode[0]) == 'c') {
            selectChallenge(journeyManager, gameState);
        }
    }

    // START TRAIN
    Train train = Train(gameState.startingLine, NULL_DIRECTION, gameState.currentStations, false, 10);
    initializeTrain(train, gameState);

    // GAME LOOP
    while (train.getCurrentStation() != gameState.destinationStation) {
        printCurrentStationInfo(train);

        unsigned int currentStationIndex = train.getCurrentStationIndex();
        unsigned int lastStationIndex = train.getScheduledStops().size() - 1;
        bool atLastStop = (currentStationIndex == 0 && train.getDirection() == DOWNTOWN) ||
                          (currentStationIndex == lastStationIndex && train.getDirection() == UPTOWN);
        if (atLastStop) {
            handleLastStop(train);
        }

        bool validInput = false;
        while (!validInput) {
            validInput = handleUserInput(train, gameState.destinationStation, gameState, journeyManager);
        }
    }

    // GAME FINISHED
    if (train.getCurrentStation() == gameState.destinationStation) {
        cout << "\nYour current Station:\n" << train.getCurrentStation();
        cout << "YOU WIN" << endl;
    }

    return 0;
}


// METHODS
void initializeTrain(Train& train, GameState& gameState) {
    train = Train(gameState.startingLine, NULL_DIRECTION, gameState.currentStations, false, 10);
    train.setCurrentStation(gameState.startingStation);
    printCurrentStationInfo(train);

    cout << "Destination Station:\n" << gameState.destinationStation;

    if (train.getCurrentStation().hasTransferLine()) {
        handleStartingLine(train);
    }

    train.setDirection(handleNewDirection(train));
}

void selectChallenge(JourneyManager& journeyManager, GameState& gameState) {
    Challenge challenge = Challenge();

    vector<Challenge> allChallenges = challenge.initializeAllChallenges();
    int count = 1;

    for (Challenge challenge : allChallenges) {
        cout << count << (count < 10 ? ":  " : ": ") << challenge << endl;
        ++count;
    }

    cout << "\nSelect a Number Challenge to Complete: ";
    string challengeChoiceIndex;
    getline(cin, challengeChoiceIndex); // Read the user's input

    int index;
    istringstream inputStringStream(challengeChoiceIndex);
    inputStringStream >> index;

    if (index >= 1 && index <= allChallenges.size()) {
        Challenge challengeChoice = allChallenges[index - 1];

        journeyManager.setStartingStation(challengeChoice.getStartStation());
        journeyManager.setDestinationStation(challengeChoice.getDestinationStation());

        gameState.startingLine = challengeChoice.getStartLine();
        SubwayMap::createStations(gameState.startingLine, gameState.currentStations);

        gameState.startingStation = journeyManager.getStartingStation();
        gameState.destinationStation = journeyManager.getDestinationStation();
    }
    else {
        cout << "Invalid challenge index. Please select a valid challenge." << endl;
    }
}


void handleStartingLine(Train &train) {
    bool validLine = false;

    while (!validLine) {
        cout << "Choose a train line to wait for at " << train.getCurrentStation().getName() << train.getCurrentStation().printTransferLinesAlternative();

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

Direction handleNewDirection(Train &train) {
    bool valid = false;
    string input = " ";

    char uptownLabelValidChar = tolower(train.getUptownLabel()[0]);
    char downtownLabelValidChar = tolower(train.getDowntownLabel()[0]);

    if (uptownLabelValidChar == downtownLabelValidChar) {
        downtownLabelValidChar = train.getDowntownLabel()[4];
        if (uptownLabelValidChar == downtownLabelValidChar) {
            downtownLabelValidChar = train.getDowntownLabel()[3];
        }
    }

    while (!valid) {
        bool isCrosstownTrain = train.getLine() == L_TRAIN || train.getLine() == S_TRAIN;

        if (isCrosstownTrain) { // special case for crosstown trains
            cout << "Would you like to enter traveling |"
                 << train.getUptownLabel()   << " ←| (" << uptownLabelValidChar   << "), or |"
                 << train.getDowntownLabel() << " →| (" << downtownLabelValidChar << ") ";
        }
        else {
            cout << "Would you like to enter traveling |"
                 << train.getUptownLabel()   << " ↑| (" << uptownLabelValidChar   << "), or |"
                 << train.getDowntownLabel() << " ↓| (" << downtownLabelValidChar << ") ";
        }

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

bool handleUserInput(Train &train, const Station &destinationStation, GameState& gameState, JourneyManager& journeyManager) {
    string input;
    if (train.getCurrentStation().hasTransferLine()) {
        cout << "Options:\n";
        cout << " - Enter a number to advance that many stations (empty advances 1 station)\n";
        cout << " - Enter 't' to transfer\n";
        cout << " - Enter 'c' to change direction\n";
        cout << " - Enter 'd' to display your Destination Station\n";
        if (gameState.isFirstTurn) {
            cout << " - Enter 'r' to refresh stations\n";
        }
    }
    else {
        cout << "Options:\n";
        cout << " - Enter a number to advance that many stations (empty advances 1 station)\n";
        cout << " - Enter 'c' to change direction\n";
        cout << " - Enter 'd' to display your Destination Station\n";
        if (gameState.isFirstTurn) {
            cout << " - Enter 'r' to reset game/stations\n";
        }
    }

    getline(cin, input);

    if (tolower(input[0]) == 'r' && input.length() == 1) {
        gameState.resetGameState(journeyManager);
        cout << "\n\n\n\n-----------GAME RESET-----------\n\n\n\n";
        initializeTrain(train, gameState);
        return true;
    }

    if (input.empty()) {                                             // advance 1 station
        return handleAdvanceOneStation(train);
    }
    else if (tolower(input[0]) == 't' && input.length() == 1) {  // prompt transfer
        return handleTransfer(train);
    }
    else if (tolower(input[0]) == 'c' && input.length() == 1) {  // change direction
        return handleChangeDirection(train);
    }
    else if (tolower(input[0]) == 'd' && input.length() == 1) {  // show destination station
        cout << "Destination Station:\n" << destinationStation;
    }
    else if (input[0] == '0' && input.length() == 1) {              // secret
        printAllStations(train);
    }
    else {                                                          // advance input<int> stations
        return handleAdvanceMultipleStations(train, input);
    }

    return false;
}


bool handleAdvanceOneStation(Train &train) {
    if (train.advanceStation()) {
        return true;
    }

    return false;
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

bool handleTransfer(Train &train) {
    if (askUserToTransfer(train)) {
        train.setDirection(handleNewDirection(train));
        train.setUptownLabel(Train::getTextForDirectionEnum(UPTOWN, train.getLine()));
        train.setDowntownLabel(Train::getTextForDirectionEnum(DOWNTOWN, train.getLine()));
    }

    return true;
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
            train.getCurrentStation().printTransferLinesAlternative();
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


void displayCurrentLineInfo(Train &train) {
    bool isCrosstownTrain = train.getLine() == L_TRAIN || train.getLine() == S_TRAIN;
    Direction currentDirection = train.getDirection();

    cout << "\nYour Current Line:\n";
    if (isCrosstownTrain) {
        cout << (currentDirection == DOWNTOWN ? // if(?) = downtown, else(:) = uptown
                 train.getDowntownLabel() + " " + Line::getTextForEnum(train.getLine()) + " Train →" :
                 train.getUptownLabel()   + " " + Line::getTextForEnum(train.getLine()) + " Train ←");
    }
    else {
        cout << (currentDirection == DOWNTOWN ? // if(?) = downtown, else(:) = uptown
                 train.getDowntownLabel() + " " + Line::getTextForEnum(train.getLine()) + " Train ↓" :
                 train.getUptownLabel()   + " " + Line::getTextForEnum(train.getLine()) + " Train ↑");
    }
    cout << endl;
}

void printCurrentStationInfo(Train &train) {
    Station currentStation = train.getCurrentStation();
    Direction currentDirection = train.getDirection();

    if (currentDirection == NULL_DIRECTION) {
        // do nothing
    }
    else {
        displayCurrentLineInfo(train);
    }

    cout << "\nYour current Station:\n" << currentStation;
}

void handleLastStop(Train &train) {
    cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "This is the last stop on this train. Everyone please leave the train, thank you for riding with MTA New York City Transit" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;

    // switch direction
    train.setDirection(train.getDirection() == DOWNTOWN ? UPTOWN : DOWNTOWN);
    string trackLabel = Train::getTextForDirectionEnum(train.getDirection(), train.getLine());

    this_thread::sleep_for(chrono::seconds(3)); // wait so user realizes
    cout << "You switched to the " << trackLabel << " platform.\n";

    this_thread::sleep_for(chrono::seconds(2));

    displayCurrentLineInfo(train);
    cout << endl;
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
                cout << setw(30) << left << stations[i].getName() << "      (Current Station)" << endl;
                cout << "    |" << endl;
            }
            else {
                cout << setw(35) << left << stations[i].getName() << stations[i].printTransferLinesAlternative();
                cout << " " << stopsAwayText << endl;
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
                cout << setw(35) << left << stations[i].getName() << stations[i].printTransferLinesAlternative();
                cout << " " << stopsAwayText << endl;
                cout << "    |" << endl;
            }
        }
    }
    cout << "------------------------------------------------------------------" << endl;
}

int getRandomStation(unsigned int numStations) {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, numStations - 1);

    return distribution(generator);
}