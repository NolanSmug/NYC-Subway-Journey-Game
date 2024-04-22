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

    void resetGameState(); // resets starting && destination stations
};

void initializeTrain(Train &train, GameState &gameState);
void selectChallenge(JourneyManager &journeyManager, GameState &gameState);

bool handleUserInput(Train &train, const Station &destinationStation, GameState &gameState);
void promptForNewDirection(Train &train);
void promptForStartingLine(Train &train);
void promptForGameMode(JourneyManager &journeyManager, GameState &gameState);

void promptForATrainDestination(Train &train, GameState &gameState);

bool advanceToNextStation(Train &train);
bool advanceMultipleStations(Train &train, string &input);
bool changeDirection(Train &train);
bool initializeTransfer(Train &train);

bool askUserToTransfer(Train &train);

void displayCurrentLineInfo(Train &train);
void displayCurrentStationInfo(Train &train);
void displayUpcomingStations(Train &train);

void announceLastStop(Train &train);

Station getRandomStation(vector<Station> &allStations);

static bool isnumber(const string &s);
static void initializeArgs(int argc, char *argv[]);


bool challengeModeFlag = true; // -c in args to set to false
bool easyModeFlag = false;     // -e in args to set to true

int main(int argc, char* argv[]) {
    // SET FLAGS FROM ARGS
    initializeArgs(argc, argv);

    // SET UP JOURNEY MANAGER
    JourneyManager journeyManager = JourneyManager();

    GameState gameState; // holds data for the current game's parameters.
    gameState.resetGameState();

    // SELECT GAME MODE (as long as `-c` is not in args)
    promptForGameMode(journeyManager, gameState);

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

        bool validInput = false;
        while (!validInput) {
            if (isAtATrainJunction) {
                promptForATrainDestination(train, gameState);
            }
            validInput = handleUserInput(train, gameState.destinationStation, gameState);
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
    train = Train(gameState.startingLine, NULL_DIRECTION, gameState.currentStations, NONE, 10);
    train.setCurrentStation(gameState.startingStation);
    train.setLineType(); // ex: Local, Express, None

    displayCurrentStationInfo(train);

    cout << "Destination Station:\n"
         << gameState.destinationStation;

    if (train.getCurrentStation().hasTransferLine()) {
        promptForStartingLine(train); // if startingStation has transfer line options
    }

    promptForNewDirection(train);
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
    getline(cin, challengeChoiceIndex);

    int index;
    istringstream inputStringStream(challengeChoiceIndex);
    inputStringStream >> index; // parse input string as integer

    if (index >= 1 && index <= allChallenges.size()) {
        Challenge challengeChoice = allChallenges[index - 1]; // retrieve selected challenge

        // update JourneyManager Object for Challenge functionality
        journeyManager.setStartingStation(challengeChoice.getStartStation());
        journeyManager.setDestinationStation(challengeChoice.getDestinationStation());

        // update GameState Object for Game functionality
        gameState.startingLine = challengeChoice.getStartLine();
        gameState.startingStation = journeyManager.getStartingStation();
        gameState.destinationStation = journeyManager.getDestinationStation();

        // update currentStations vector based on the Challenge's startingLine
        SubwayMap::createStations(gameState.startingLine, gameState.currentStations);
    }
    else {
        cout << "Invalid challenge index. Please select a valid challenge." << endl;
    }
}


void promptForStartingLine(Train &train) {
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

void promptForNewDirection(Train &train) {
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

void promptForGameMode(JourneyManager &journeyManager, GameState &gameState) {

    if (challengeModeFlag) {
        string gameMode;
        cout << "Would you like to play Normal Mode (any key) or Challenge Mode (c)? ";

        getline(cin, gameMode);

        if (tolower(gameMode[0]) == 'c') {
            selectChallenge(journeyManager, gameState);
        }
    }
}

void promptForATrainDestination(Train &train, GameState &gameState) {
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

bool handleUserInput(Train &train, const Station &destinationStation, GameState& gameState) {
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
    // (https://stackoverflow.com/a/16011109/23352980)
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
        cout << "Destination Station:\n" << destinationStation;
    }
    else if (inputChar == '0') {                        // secret
        displayUpcomingStations(train);
    }
    else {                                              // advance input<int> stations
        return advanceMultipleStations(train, input);
    }
    input.clear();

    return false;
}


bool advanceToNextStation(Train &train) {
    if (train.advanceStation()) {
        return true;
    }

    return false;
}

bool changeDirection(Train &train) {
    train.setDirection(train.getDirection() == DOWNTOWN ? UPTOWN : DOWNTOWN);
    string trackLabel = Train::getTextForDirectionEnum(train.getDirection(), train.getLine());
    cout << "\nYou switched to the "
         << trackLabel
         << " platform." << endl;

    return true;
}

bool advanceMultipleStations(Train &train, string &input) {
    int stationsToAdvance;

    istringstream inputStringStream(input);
    if (inputStringStream >> stationsToAdvance && train.advanceStation(stationsToAdvance)) {
        return true;
    }

    return false;
}

bool initializeTransfer(Train &train) {
    if (askUserToTransfer(train)) { // if user has chosen a valid transfer line
        promptForNewDirection(train);

        train.setUptownLabel(Train::getTextForDirectionEnum(UPTOWN, train.getLine()));
        train.setDowntownLabel(Train::getTextForDirectionEnum(DOWNTOWN, train.getLine()));
    }

    return true;
}

bool askUserToTransfer(Train &train) {
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


void displayCurrentLineInfo(Train &train) {
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


    easyModeFlag ? displayUpcomingStations(train) : void(); // easy mode flag (ignore otherwise)

    cout << "\n\nCurrent Line:\n" << currentLineInfo << endl;
}

void displayCurrentStationInfo(Train &train) {
    Direction currentDirection = train.getDirection();

    if (currentDirection == NULL_DIRECTION) {
        // do nothing (the user is not currently on a line)
    }
    else {
        displayCurrentLineInfo(train);
    }

    cout << "\nCurrent Station:\n" << train.getCurrentStation();
}

void announceLastStop(Train &train) {
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


void displayUpcomingStations(Train &train) {
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

int getRandomStation(unsigned int numStations) {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, numStations - 1);

    return distribution(generator);
}

Station getRandomStation(vector<Station> &allStations) {
    static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    static std::mt19937_64 generator1(seed);
    static std::default_random_engine generator2(generator1());
    static std::uniform_int_distribution<std::size_t> dist(0, allStations.size() - 1);

    std::size_t randomIndex = dist(generator2);

    return allStations[randomIndex];
}

void GameState::resetGameState() { // if user wants to re-shuffle their stations
    vector<Station> allStations;
    SubwayMap::createStations(NULL_TRAIN, allStations);

    startingLine = Line::getRandomLine();
    SubwayMap::createStations(startingLine, currentStations);

    startingStation = getRandomStation(currentStations);

    destinationStation = startingStation;
    while (startingStation == destinationStation) {
        destinationStation = getRandomStation(allStations);
    }

    isFirstTurn = true;
}

static bool isnumber(const string &s) {
    return all_of(s.begin(), s.end(), ::isdigit);
}

void initializeArgs(int argc, char* argv[]) {
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
