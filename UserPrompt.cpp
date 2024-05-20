//
// Created by Nolan Cyr on 5/18/24.
//

#include "UserPrompt.h"

UserInterface uiPrompt;

void UserPrompt::promptForChallengeSelection(GameState &gameState) {
    Challenge challenge;
    challenge.initializeAllChallenges();

    uiPrompt.displayAllChallenges(challenge);

    int choiceIndex;
    bool validChoice = false;

    while (!validChoice) {
        cout << "\nSelect a Number Challenge to Complete: ";
        string input;
        getline(cin,input);

        if (isnumber(input)) {
            choiceIndex = stoi(input);
            bool wantsCustomChallenge = choiceIndex == challenge.getAllChallenges().size() + 1;

            if (choiceIndex >= 1 && choiceIndex <= challenge.getAllChallenges().size()) {
                Challenge selectedChallenge = challenge.getAllChallenges()[choiceIndex - 1];

                gameState.startingLine = selectedChallenge.getStartLine();
                gameState.startingStation = selectedChallenge.getStartStation();
                gameState.destinationStation = selectedChallenge.getDestinationStation();
                gameState.currentStation = gameState.startingStation;

                SubwayMap::createStations(gameState.startingLine, gameState.currentStations);

                validChoice = true;
            }
            else if (wantsCustomChallenge) {
                promptsForCustomChallenge(challenge);
                uiPrompt.displayAllChallenges(challenge);
            }
            else {
                cout << "Invalid challenge index. Please select a valid challenge.";
            }
        }
        else {
            cout << "Invalid input. Please enter a number.";
        }
    }
}


void UserPrompt::promptsForCustomChallenge(Challenge &challenge) {
    LineName chosenStartLine = promptLineSelection(true); // prompt for start line
    if (chosenStartLine == NULL_TRAIN) {
        return; // user wants to go back
    }
    Station startStation = promptStationFromLine(chosenStartLine, true); // prompt for s station

    LineName chosenDestinationLine;
    bool validDestinationLine = false;

    while (!validDestinationLine) {
        chosenDestinationLine = promptLineSelection(false); // prompt for destination line
        if (chosenDestinationLine == NULL_TRAIN) {
            return; // user wants to go back
        }
        validDestinationLine = true;
    }
    Station destStation = promptStationFromLine(chosenDestinationLine, false); // prompt for d station

    // create and save the challenge csv
    Challenge newChallenge = Challenge(startStation, destStation, CUSTOM);
    challenge.addNewChallenge(newChallenge);
    challenge.writeNewChallenge(newChallenge);
}


void UserPrompt::promptForStartingLine(Train &train) {
    bool validLine = false;

    while (!validLine) {
        cout << "Choose a train line to wait for at "
             << train.getCurrentStation().getName()
             << train.getCurrentStation().getTransferLinesString();

        string lineChoice;
        getline(cin, lineChoice);
        transform(lineChoice.begin(), lineChoice.end(), lineChoice.begin(), ::toupper);

        if (train.transferToLine(Line::stringToLineEnum(lineChoice),train.getCurrentStation())) {
            validLine = true;
        }
        else {
            cout << "Invalid line choice. " << endl;
        }
    }
}

void UserPrompt::promptForDirection(Train &train) {
    bool valid = false;
    string input = " ";

    char uptownLabelValidChar = tolower(train.getUptownLabel()[0]);
    char downtownLabelValidChar = tolower(train.getDowntownLabel()[0]);

    if (uptownLabelValidChar == downtownLabelValidChar) {
        downtownLabelValidChar = train.getDowntownLabel()[4];
        if (uptownLabelValidChar == downtownLabelValidChar) {  // just ignore this mess it won't need to be changed
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
            train.setDirection(tolower(input[0]) == downtownLabelValidChar ? DOWNTOWN : UPTOWN);
            valid = true;
        }
        else {
            cout << "Invalid direction choice." << endl;
        }
    }
}

void UserPrompt::promptForGameMode(GameState &gameState) {

    if (Game::challengeModeFlag) {
        string gameMode;
        cout << "Would you like to play Normal Mode (any key) or Challenge Mode (c)? ";

        getline(cin, gameMode);

        if (tolower(gameMode[0]) == 'c') {
            promptForChallengeSelection(gameState);
        }
    }
}

void UserPrompt::promptForAtRockawayBranch(Train &train, GameState &gameState) {
    string input;
    bool validInput = false;

    Station rockawayBlvd = train.getCurrentStation();

    cout << "\nYou have reached a junction on the A train line. Please choose your desired "
         << "destination from the following options:" << endl;
    cout << " - Far Rockaway–Mott Av (F)" << endl;
    cout << " - Lefferts Boulevard   (L)" << endl;
    cout << " - I'm confused! Help?  (H)\n" << endl;

    while (!validInput) {
        cout << "Enter a destination (F or L): ";
        getline(cin, input);
        if (input.length() > 1) {
            continue;
        }

        char inputChar = toupper(input[0]);
        if (inputChar == 'F') {
            SubwayMap::updateStopsForLine(A_ROCKAWAY_MOTT_TRAIN,gameState.currentStations);
            train.setLine(A_ROCKAWAY_MOTT_TRAIN);

            train.setScheduledStops(gameState.currentStations);
            train.setCurrentStation(rockawayBlvd);

            validInput = true;
        }
        else if (inputChar == 'L') {
            SubwayMap::updateStopsForLine(A_LEFFERTS_TRAIN,gameState.currentStations);
            train.setLine(A_LEFFERTS_TRAIN);

            train.setScheduledStops(gameState.currentStations);
            train.setCurrentStation(rockawayBlvd);

            validInput = true;
        }
        else if (inputChar == 'H') {
            cout << "\nIn NYC, the A train actually has a unique junction at Rockaway Blvd, where the track splits into two branches, each headed to a different destination.\n\n";
            cout << "                      /----- (8 stops) ---- Far Rockaway–Mott Av\n";
            cout << "Rockaway Blvd ------ {\n";
            cout << "                      \\----- (2 stops) ---- Lefferts Blvd\n\n";
            cout << "it is important to check which A train you are getting on if your destination station is along one of these branches.\n\n\n";
        }
        else {
            cout << "Invalid input. ";
        }
    }

    uiPrompt.displayCurrentLineInfo(train);
    cout << endl;
}




bool UserPrompt::promptForTransfer(Train &train) {
    Station currentStation = train.getCurrentStation();
    string input;

    bool alreadyListedTransfers = false;
    while (true) {
        cout << "Which line would you like to transfer to? ";
        cout << (!alreadyListedTransfers ? "(t to list transfer lines) | " : "");
        cout << "(e to exit) ";

        getline(cin, input);
        transform(input.begin(), input.end(), input.begin(), ::toupper);

        if (tolower(input[0]) == 't') {
            cout << currentStation.getTransferLinesString().substr(1) << endl; // need substr to strip leading space
            alreadyListedTransfers = true;
        }
        else if (input[0] == 'E' || input[0] == 'e') {
            return false;
        }
        else if (train.transferToLine(Line::stringToLineEnum(input), currentStation)) {
            return true;
        }
        else {
            cout << "Invalid input. Please try again." << endl; // Add this line to provide better feedback for invalid input
        }
    }
}


LineName UserPrompt::promptLineSelection(bool isStartingStation) {
    LineName chosenLine;
    bool validLine = false;
    string BACK_INPUT_MATCH = "9";

    string stationType = isStartingStation ? "STARTING" : "DESTINATION";
    string promptMessage = "Choose a train line to list stations for " + stationType + " STATION selection (i to list lines): ";

    while (!validLine) {
        cout << promptMessage;

        string input;
        getline(cin, input);
        transform(input.begin(), input.end(), input.begin(), ::toupper);

        if (Line::isValidAvaliableLine(input)) {
            chosenLine = Line::stringToLineEnum(input);
            cout << "You chose the (" << Line::getTextForEnum(chosenLine) << " Train). ('9' to go back), ('valid_line' to change line) or any other key to continue with selection: ";
            string input2;
            getline(cin, input2);
            transform(input.begin(), input.end(), input.begin(), ::toupper);

            if (input2 == BACK_INPUT_MATCH) {
                return NULL_TRAIN; // or any other default value you prefer
            }
            else if (Line::isValidAvaliableLine(input2)) {
                return Line::stringToLineEnum(input2);
            }
            else {
                validLine = true;
            }
        }
        else if (tolower(input[0]) == 'i') {
            cout << AvaliableLines << endl;
        }
        else {
            cout << "Invalid line choice. ";
        }
    }

    return chosenLine;
}

Station UserPrompt::promptStationFromLine(LineName line, bool isStartingStation) {
    vector<Station> stations;
    SubwayMap::createStations(line,stations);

    uiPrompt.displayStationsFor(stations);

    string prompt = "Enter an ID for your desired " + string(isStartingStation ? "STARTING" : "DESTINATION") + " station: ";
    string chosenId;
    cout << prompt;
    getline(cin, chosenId);

    return Station::getStation(chosenId);
}

string UserPrompt::getInput(Train &train, GameState &gameState) {
    string input;
    cout << "Options:\n";
    cout << " - Enter a number to advance that many stations (empty advances 1 station)\n";
    cout << " - Enter 'c' to change direction\n";
    cout << " - Enter 'd' to display your Destination Station\n";

    if (train.getCurrentStation().hasTransferLine()) {
        cout << " - Enter 't' to transfer\n";
    }
    if (gameState.isFirstTurn) {
        cout << " - Enter 'r' to refresh stations\n";
    }

    getline(cin, input);
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    return input;
}

bool UserPrompt::promptToPlayAgain() {
    string playAgainInput;
    cout << "\nPlay again? (y/n): ";
    getline(cin, playAgainInput);
    playAgainInput.erase(remove(playAgainInput.begin(), playAgainInput.end(), ' '), playAgainInput.end());

    bool wantsToPlayAgain = tolower(playAgainInput[0]) == 'y'; // variable can be removed, but readbility is best

    return wantsToPlayAgain;
}


bool UserPrompt::isnumber(const string &s) {
    return all_of(s.begin(), s.end(), ::isdigit);
}