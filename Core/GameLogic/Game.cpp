//
// Created by Nolan Cyr on 5/5/24.
//

#include "Game.h"

void Game::runGame() {
    // Initialize all NYC stations
    Station::initializeAllStations();

    // Create GameState (holds data for the current game's parameters)
    GameState gameState;
    gameState.resetGameState();

    // Select Game Mode
    prompt.promptForGameMode(gameState);

    // Start Train
    Train train;
    initializeTrain(train, gameState);

    // Game Loop
    while (train.getCurrentStation() != gameState.destinationStation) {
        ui.displayCurrentStationInfo(train);

        train.updateTrainState();

        if (train.isAtRockawayBranchJunction()) {
            prompt.promptForAtRockawayBranch(train, gameState);
        }
        else if (train.isAtLastStop()) {
            ui.announceLastStop(train);
            train.reverseDirection();
        }

        handleUserInput(train, gameState);
    }

    // GAME FINISHED (loop exited)
    ui.displayGameWin(train, gameState.gameStats);
}


// METHODS
void Game::initializeTrain(Train& train, GameState& gameState) {
    train = Train(gameState.startingLine, NULL_DIRECTION, gameState.currentStations, train.setLineType(), 10);
    train.setCurrentStation(gameState.currentStation);

    ui.displayCurrentStationInfo(train);
    ui.displayDestinationStationInfo(gameState.destinationStation);

    if (train.getCurrentStation().hasTransferLine()) {
        prompt.promptForStartingLine(train); // if startingStation has transfer line options
    }

    prompt.promptForDirection(train);

    gameState.gameStats.addToLinesVisited(train.getLine());
}


void Game::resetGame(GameState &gameState) {
    gameState.resetGameState();
    ui.displayGameReset();
}


void Game::handleUserInput(Train& train, GameState& gameState) {
    bool validInput = false;
    ui.displayAvailableTrainActions(train, gameState);

    while (!validInput) {
        string input = prompt.getInput();
        InputAction inputAction = prompt.parseInputToInputAction(input);

        switch (inputAction) {
            case RESET_GAME:
                resetGame(gameState);
                initializeTrain(train, gameState);
                validInput = true;
                break;

            case ADVANCE_STATION:
                validInput = advanceToNextStation(train, gameState);
                break;

            case TRANSFER_LINE:
                validInput = initializeTransfer(train, gameState);
                break;

            case CHANGE_DIRECTION:
                train.reverseDirection();
                validInput = true;
                break;

            case DISPLAY_DESTINATION:
                ui.displayDestinationStationInfo(gameState.destinationStation);
                break;

            case DISPLAY_UPCOMING_STATIONS:
                ui.displayUpcomingStations(train);
                validInput = true;
                break;

            default:
                validInput = advanceMultipleStations(train, gameState, input);
                break;
        }
    }
}


bool Game::advanceToNextStation(Train &train, GameState &gameState) {
    if (train.advanceStation()) {
        gameState.gameStats.incrementStationsVisited(train.getCurrentStation().getBorough());
        return true;
    }

    return false;
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
