//
// Created by Nolan Cyr on 5/5/24.
//

#include "Game.h"

void Game::runGame(int argc, char* argv[]) {
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

        train.updateTrainState();

        if (train.isAtRockawayBranchJunction()) {
            prompt.promptForAtRockawayBranch(train, gameState);
        }
        else if (train.isAtLastStop()) {
            train.reverseDirection();
            ui.announceLastStop(train);
        }

        validInput = false;
        while (!validInput) {
            validInput = handleUserInput(train, gameState);
        }
    }

    // GAME FINISHED (loop exited)
    if (train.getCurrentStation() == gameState.destinationStation) {
        ui.displayGameWin(train, gameState.gameStats);
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

    gameState.gameStats.addToLinesVisited(train.getLine());


    prompt.promptForDirection(train);
}


void Game::resetGame(GameState &gameState) {
    gameState.resetGameState();
    ui.displayGameReset();
}


bool Game::handleUserInput(Train& train, GameState& gameState) {
    string input = prompt.getInput(train, gameState);

    switch (tolower(input[0])) {
        case 'r':
            resetGame(gameState);
            initializeTrain(train, gameState);
            return true;
        case '\0':  // Empty input
            return advanceToNextStation(train, gameState);
        case 't':
            return initializeTransfer(train, gameState);
        case 'c':
            return changeDirection(train);
        case 'd':
            ui.displayDestinationStationInfo(gameState.destinationStation);
            return false;
        case '0':
            ui.displayUpcomingStations(train);
            return true;
        default:
            return advanceMultipleStations(train, gameState, input);
    }

}


bool Game::advanceToNextStation(Train &train, GameState &gameState) {
    if (train.advanceStation()) {
        gameState.gameStats.incrementStationsVisited(train.getCurrentStation().getBorough());
        return true;
    }

    return false;
}

bool Game::changeDirection(Train &train) {
    train.setDirection(train.getDirection() == DOWNTOWN ? UPTOWN : DOWNTOWN);
    ui.displayDirectionChange(train);

    return true;
}

bool Game::advanceMultipleStations(Train &train, GameState &gameState, string &input) {
    int stationsToAdvance;

    istringstream inputStringStream(input);
    if (inputStringStream >> stationsToAdvance && train.advanceStation(stationsToAdvance)) {

        gameState.gameStats.incrementStationsVisited(stationsToAdvance);
        return true;
    }

    return false;
}

bool Game::initializeTransfer(Train &train, GameState &gameState) {
    if (prompt.promptForTransfer(train)) { // if user has chosen a valid transfer line
        ui.displayTransferSuccess(train);
        prompt.promptForDirection(train);
        gameState.gameStats.addToLinesVisited(train.getLine());

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
                GameState::challengeModeFlag = false;
            }
            else if (arg == "-e") {
                GameState::easyModeFlag = true;
            }
        }
    }
}

