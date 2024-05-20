//
// Created by Nolan Cyr on 5/5/24.
//

#include "Game.h"
#include "UserInterface.h"
#include "UserPrompt.h"

// Definitions of non-static data members
UserInterface ui;
UserPrompt prompt;

bool Game::challengeModeFlag = true; // -c in args to set to false
bool Game::easyModeFlag = false;     // -e in args to set to true

void Game::startGame(int argc, char* argv[]) {
    // SET FLAGS FROM ARGS
    initializeArgs(argc, argv);

    // INITIALIZE ALL NYC STATIONS
    Station::initializeAllStations();

    // SET UP GAME STATE (holds data for the current game's parameters)
    GameState gameState;
    gameState.resetGameState();

    // SELECT GAME MODE (as long as `-c` is not in args)
    prompt.promptForGameMode(gameState);

    // START TRAIN
    Train train;
    initializeTrain(train, gameState);

    // GAME LOOP
    bool validInput;
    while (train.getCurrentStation() != gameState.destinationStation) {
        ui.displayCurrentStationInfo(train);

        bool isAtRockawayBranchJunction;
        bool isAtEndOfLine;
        updateTrainState(train, gameState, isAtRockawayBranchJunction, isAtEndOfLine);

        if (isAtRockawayBranchJunction) {
            prompt.promptForAtRockawayBranch(train, gameState);
        }
        else if (isAtEndOfLine) {
            ui.announceLastStop(train);
        }

        validInput = false;
        while (!validInput) {
            validInput = handleUserInput(train, gameState);
        }
    }

    // GAME FINISHED (loop exited)
    if (train.getCurrentStation() == gameState.destinationStation) {
        cout << "\nYour current Station:\n" << train.getCurrentStation();
        cout << "YOU WIN" << endl << endl;
    }
}


// METHODS
void Game::initializeTrain(Train& train, GameState& gameState) {
    train = Train(gameState.startingLine, NULL_DIRECTION, gameState.currentStations, NONE, 10);
    train.setCurrentStation(gameState.currentStation);
    train.setLineType(); // ex: Local, Express, None

    ui.displayCurrentStationInfo(train);
    ui.displayDestinationStationInfo(gameState.destinationStation);

    if (train.getCurrentStation().hasTransferLine()) {
        prompt.promptForStartingLine(train); // if startingStation has transfer line options
    }

    prompt.promptForDirection(train);
}


void Game::resetGame(GameState &gameState) {
    gameState.resetGameState();
    cout << "\n\n\n\n-----------GAME RESET-----------\n\n\n\n";
}

void Game::updateTrainState(Train& train, bool& isAtATrainJunction, bool& atLastStop) {
    unsigned int currentStationIndex = train.getCurrentStationIndex();
    unsigned int lastStationIndex = train.getScheduledStops().size() - 1;

    isAtATrainJunction = train.getCurrentStation().getName() == "Rockaway Blvd" &&
                              train.getDirection() == DOWNTOWN;
    atLastStop = ((currentStationIndex == 0                && train.getDirection() == DOWNTOWN) ||
                       (currentStationIndex == lastStationIndex && train.getDirection() == UPTOWN))   &&
                      !isAtATrainJunction;
}

bool Game::handleUserInput(Train &train, GameState& gameState) {
    string input = prompt.getInput(train, gameState);
    char inputChar = tolower(input[0]);

    if (inputChar == 'r') {
        resetGame(gameState);
        initializeTrain(train,gameState);
        return true;
    }
    else if (input.empty()) {
        return advanceToNextStation(train);
    }
    else if (inputChar == 't') {
        return initializeTransfer(train);
    }
    else if (inputChar == 'c') {
        return changeDirection(train);
    }
    else if (inputChar == 'd') {
        ui.displayDestinationStationInfo(gameState.destinationStation);
        return false;
    }
    else if (inputChar == '0') {
        ui.displayUpcomingStations(train);
        return true;
    }
    else {
        return advanceMultipleStations(train, input);
    }
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
    if (prompt.promptForTransfer(train)) { // if user has chosen a valid transfer line
        prompt.promptForDirection(train);

        train.setUptownLabel(Train::getTextForDirectionEnum(UPTOWN, train.getLine()));
        train.setDowntownLabel(Train::getTextForDirectionEnum(DOWNTOWN, train.getLine()));

        return true;
    }

    return false; // user has not chosen a valid transfer line
}



void Game::initializeArgs(int argc, char* argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {

            string arg = argv[i];

            if (arg == "-c") {
                Game::challengeModeFlag = false;
            }
            else if (arg == "-e") {
                Game::easyModeFlag = true;
            }
        }
    }
}

