//
// Created by Nolan Cyr on 5/5/24.
//

#include "Game.h"

bool challengeModeFlag = true; // -c in args to set to false
bool easyModeFlag = false;     // -e in args to set to true

void Game::startGame(int argc, char* argv[]) {
    // SET FLAGS FROM ARGS
    initializeArgs(argc, argv);

    // INITIALIZE ALL NYC STATIONS
    Station::initializeAllStations();

    // SET UP GAME STATE (holds data for the current game's parameters)
    GameState gameState;
    gameState.resetGameState();

    // SELECT GAME MODE (as long as `-c` is not in args)
    promptForGameMode(gameState);

    // START TRAIN
    Train train;
    initializeTrain(train, gameState);

    // GAME LOOP
    while (train.getCurrentStation() != gameState.destinationStation) {
        displayCurrentStationInfo(train);

        unsigned int currentStationIndex = train.getCurrentStationIndex();
        unsigned int lastStationIndex = train.getScheduledStops().size() - 1;
        bool atLastStop = (currentStationIndex == 0                && train.getDirection() == DOWNTOWN) ||
                          (currentStationIndex == lastStationIndex && train.getDirection() == UPTOWN);
        bool isAtATrainJunction = train.getCurrentStation().getName() == "Rockaway Blvd" &&
                                  train.getDirection() == DOWNTOWN;

        if (atLastStop && !isAtATrainJunction) {
            announceLastStop(train);
        }
        if (isAtATrainJunction) {
            promptForATrainDestination(train, gameState);
        }

        bool validInput = false;
        while (!validInput) {
            validInput = handleUserInput(train,gameState);
        }
    }

    // GAME FINISHED
    if (train.getCurrentStation() == gameState.destinationStation) {
        cout << "\nYour current Station:\n" << train.getCurrentStation();
        cout << "YOU WIN" << endl;
    }

}


// METHODS
void Game::initializeTrain(Train& train, GameState& gameState) {
    train = Train(gameState.startingLine, NULL_DIRECTION, gameState.currentStations, NONE, 10);
    train.setCurrentStation(gameState.currentStation);
    train.setLineType(); // ex: Local, Express, None

    displayCurrentStationInfo(train);

    cout << "Destination Station:\n"
         << gameState.destinationStation;

    if (train.getCurrentStation().hasTransferLine()) {
        promptForStartingLine(train); // if startingStation has transfer line options
    }

    promptForDirection(train);
}

void Game::promptForChallengeSelection(GameState &gameState) {
    Challenge challenge = Challenge();
    challenge.initializeAllChallenges();

    displayAllChallenges(challenge);

    bool validChoice = false;
    while (!validChoice) {
        cout << "\nSelect a Number Challenge to Complete: ";
        string challengeChoiceIndex;
        getline(cin, challengeChoiceIndex);

        int index;
        istringstream inputStringStream(challengeChoiceIndex);
        if (inputStringStream >> index && index >= 1 && index <= challenge.getAllChallenges().size()) {
            Challenge challengeChoice = challenge.getAllChallenges()[index - 1]; // retrieve selected challenge

            // update GameState parameters for Game functionality
            gameState.startingLine = challengeChoice.getStartLine();
            gameState.startingStation = challengeChoice.getStartStation();
            gameState.destinationStation = challengeChoice.getDestinationStation();
            gameState.currentStation = gameState.startingStation;

            // update currentStations vector based on the Challenge's startingLine
            SubwayMap::createStations(gameState.startingLine, gameState.currentStations);

            validChoice = true;
        }
        else if (index == challenge.getAllChallenges().size() + 1) {
            promptsForCustomChallenge(challenge);
            displayAllChallenges(challenge);
        }
        else {
            cout << "Invalid challenge index. Please select a valid challenge." << endl;
        }
    }
}

void Game::promptsForCustomChallenge(Challenge &challenge) {
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


void Game::promptForStartingLine(Train &train) {
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

void Game::promptForDirection(Train &train) {
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
            cout << "Invalid input. ";
        }
    }
}

void Game::promptForGameMode(GameState &gameState) {

    if (challengeModeFlag) {
        string gameMode;
        cout << "Would you like to play Normal Mode (any key) or Challenge Mode (c)? ";

        getline(cin, gameMode);

        if (tolower(gameMode[0]) == 'c') {
            promptForChallengeSelection(gameState);
        }
    }
}

void Game::promptForATrainDestination(Train &train, GameState &gameState) {
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

    displayCurrentLineInfo(train);
    cout << endl;
}

bool Game::handleUserInput(Train &train, GameState& gameState) {
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

    // remove any whitespaces in input
    /// (https://stackoverflow.com/a/16011109/23352980)
    input.erase(remove(input.begin(), input.end(), ' '), input.end());

    // exit if input is known to be immediately invalid
    if (!input.empty() && input.length() != 1 && !isnumber(input)) { // input is not empty, not 1 char, and NaN
        return false;
    }
    char inputChar = tolower(input[0]);

    // RESET GAME
    if (inputChar == 'r') {
        gameState.resetGameState();
        cout << "\n\n\n\n-----------GAME RESET-----------\n\n\n\n";
        initializeTrain(train, gameState);
        return true;
    }

    if (input.empty()) {                                // advance 1 station
        return advanceToNextStation(train);
    }
    else if (inputChar == 't') {                        // prompt transfer
        return initializeTransfer(train);
    }
    else if (inputChar == 'c') {                        // change direction
        return changeDirection(train);
    }
    else if (inputChar == 'd') {                        // show destination station
        cout << "Destination Station:\n" << gameState.destinationStation;
    }
    else if (inputChar == '0') {                        // secret
        displayUpcomingStations(train);
    }
    else {                                              // advance input<int> stations
        return advanceMultipleStations(train, input);
    }
    input.clear();

    if (gameState.isFirstTurn) {
        gameState.isFirstTurn = false;
    }

    return false;
}


bool Game::advanceToNextStation(Train &train) {
    if (train.advanceStation()) {
        return true;
    }

    return false;
}

bool Game::changeDirection(Train &train) {
    train.setDirection(train.getDirection() == DOWNTOWN ? UPTOWN : DOWNTOWN);
    string trackLabel = Train::getTextForDirectionEnum(train.getDirection(), train.getLine());
    cout << "\nYou switched to the "
         << trackLabel
         << " platform." << endl;

    return true;
}

bool Game::advanceMultipleStations(Train &train, string &input) {
    int stationsToAdvance;

    istringstream inputStringStream(input);
    if (inputStringStream >> stationsToAdvance && train.advanceStation(stationsToAdvance)) {
        return true;
    }

    return false;
}

bool Game::initializeTransfer(Train &train) {
    if (promptForTransfer(train)) { // if user has chosen a valid transfer line
        promptForDirection(train);

        train.setUptownLabel(Train::getTextForDirectionEnum(UPTOWN, train.getLine()));
        train.setDowntownLabel(Train::getTextForDirectionEnum(DOWNTOWN, train.getLine()));
    }

    return true;
}

bool Game::promptForTransfer(Train &train) {
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
        else if (input[0] == 'x') {
            return false;
        }
        else if (train.transferToLine(Line::stringToLineEnum(input), currentStation)) {
            cout << endl;
            return true;
        }
        else {
            cout << "The " << input << " Train does not stop at "
                 << currentStation.getName()
                 << currentStation.getTransferLinesString() << endl;
        }
    }
}


void Game::displayCurrentLineInfo(Train &train) {
    Direction currentDirection = train.getDirection();
    LineName currentLine = train.getLine();
    LineType currentLineType = train.setLineType();

    bool isCrosstownTrain = train.getLine() == L_TRAIN || train.getLine() == S_TRAIN;

    string currentLineStr = Line::getTextForEnum(currentLine);
    string currentLineTypeStr = Line::getLineTypeString(currentLineType);
    string currentDirectionLabel = currentDirection == DOWNTOWN
                                   ? train.getDowntownLabel()
                                   : train.getUptownLabel();
    string directionArrowSymbol = isCrosstownTrain
                                  ? (currentDirection == DOWNTOWN ? "→" : "←") // second conditional for correct direction
                                  : (currentDirection == DOWNTOWN ? "↓" : "↑");

    string currentLineInfo; // string to be filled

    if (currentLineType == NONE) {
        currentLineInfo = currentDirectionLabel + " " + currentLineStr +                            " Train " + directionArrowSymbol;
    }
    else {
        currentLineInfo = currentDirectionLabel + " " + currentLineStr + " " + currentLineTypeStr + " Train " + directionArrowSymbol;
    }

    if (easyModeFlag) {
        displayCurrentLineInfo(train);
    }
    cout << "\n\nCurrent Line:\n" << currentLineInfo << endl;
}

void Game::displayCurrentStationInfo(Train &train) {
    Direction currentDirection = train.getDirection();

    if (currentDirection == NULL_DIRECTION) {
        // do nothing (the user is not currently on a line)
    }
    else {
        displayCurrentLineInfo(train);
    }
    train.getCurrentStation();

    cout << "\nCurrent Station:\n" << train.getCurrentStation();
}

void Game::announceLastStop(Train &train) {
    cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "This is the last stop on this train. Everyone please leave the train, thank you for riding with MTA New York City Transit" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;

    // special case for last stop on the different A train types
    if (train.getLine() == A_ROCKAWAY_MOTT_TRAIN || train.getLine() == A_LEFFERTS_TRAIN) {
        train.setLine(A_TRAIN);
    }

    // switch direction
    train.setDirection(train.getDirection() == DOWNTOWN ? UPTOWN : DOWNTOWN);
    string trackLabel = Train::getTextForDirectionEnum(train.getDirection(), train.getLine());

    this_thread::sleep_for(chrono::seconds(2)); // wait so user realizes

    cout << "You switched to the "
         << trackLabel
         << " platform.\n";

    this_thread::sleep_for(chrono::seconds(1));

    displayCurrentLineInfo(train);
    cout << endl;
}

/** This method would not have been made possible without assistance from Claude,
    an AI assistant created by Anthropic (https://www.anthropic.com)
 */
void Game::displayUpcomingStations(Train &train) {
    string currentStationID = train.getCurrentStation().getId();
    vector<Station> stations = train.getScheduledStops();
    Direction currentDirection = train.getDirection();
    int length = train.getScheduledStops().size();
    int currentStationIndex = train.getCurrentStationIndex();

    cout << "------------------------------------------------------------------" << endl;

    if (currentDirection == UPTOWN) {
        for (int i = length - 1; i >= currentStationIndex; i--) {
            int stopsAway = abs(i - currentStationIndex);
            string stopsAwayText = (stopsAway == 0) ? ""
                                                    : (stopsAway == 1) ? "(Next Stop)"
                                                                       : "(" + to_string(stopsAway) + " stops away)";

            if (stations[i].getId() == currentStationID) {
                cout << setw(30) << left << stations[i].getName() << "      (Current Station)" << endl;
                cout << "    |" << endl;
            }
            else {
                cout << setw(35) << left << stations[i].getName()
                     << stations[i].getTransferLinesString()
                     << " " << stopsAwayText << endl;
                cout << "    |" << endl;
            }
        }
        cout << "    ↑" << endl;
    }
    else { // DOWNTOWN
        cout << "    ↓" << endl;
        for (int i = train.getCurrentStationIndex(); i >= 0; i--) {
            int stopsAway = abs(train.getCurrentStationIndex() - i);
            string stopsAwayText = (stopsAway == 0) ? ""
                                                    : (stopsAway == 1) ? "(Next Stop)"
                                                                       : "(" + to_string(stopsAway) + " stops away)";

            if (stations[i].getId() == currentStationID) {
                cout << setw(30) << left << stations[i].getName() << " **  Current Station  **" << endl;
                cout << "    |" << endl;
            }
            else {
                cout << setw(35) << left << stations[i].getName()
                     << stations[i].getTransferLinesString()
                     << " " << stopsAwayText << endl;
                cout << "    |" << endl;
            }
        }
    }

    cout << "------------------------------------------------------------------" << endl;
}

void Game::displayAllChallenges(Challenge challenge) {
    int count = 1;
    for (Challenge challenge : challenge.getAllChallenges()) {
        cout << count << (count < 10 ? ":  " : ": ") << challenge << endl;
        ++count;
    }
    cout << count << ": New Custom Journey" << endl;
}

void Game::displayStationsFor(vector<Station> stations) {
    cout << "  ID  |         Station Name         |\n";
    cout << "------|------------------------------|\n";
    for (auto it = stations.rbegin(); it != stations.rend(); ++it) {
        Station station = *it;
        cout << " " << station.getId() << "  |  " << station.getName() << endl;
    }
}

LineName Game::promptLineSelection(bool isStartingStation) {
    LineName chosenLine;
    bool validLine = false;
    string BACK_INPUT_MATCH = "9";

    string stationType = isStartingStation ? "STARTING" : "DESTINATION";
    string promptMessage = "Choose a train line to list stations for " + stationType + " STATION selection (i to list them): ";

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

Station Game::promptStationFromLine(LineName line, bool isStartingStation) {
    vector<Station> stations;
    SubwayMap::createStations(line,stations);

    displayStationsFor(stations);

    string prompt = "Enter an ID for your desired " + string(isStartingStation ? "STARTING" : "DESTINATION") + " station: ";
    string chosenId;
    cout << prompt;
    getline(cin, chosenId);

    return Station::getStation(chosenId);
}

void GameState::resetGameState() { // if user wants to re-shuffle their stations
    startingLine = Line::getRandomLine();
    isFirstTurn = true;

    SubwayMap::createStations(startingLine, currentStations); // fill currentStations vector for currentLine

    startingStation = Station::getRandomStation(currentStations);
    do {
        destinationStation = Station::getRandomStation(Station::allNycStations); // select random destination station
    } while (startingStation == destinationStation); // ensure starting != destinatio            n

    currentStation = startingStation;
}

bool Game::isnumber(const string &s) {
    return all_of(s.begin(), s.end(), ::isdigit);
}

void Game::initializeArgs(int argc, char* argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {

            string arg = argv[i];

            if (arg == "-c") {
                challengeModeFlag = false;
            }
            else if (arg == "-e") {
                easyModeFlag = true;
            }
        }
    }
}
