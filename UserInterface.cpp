//
// Created by Nolan Cyr on 5/18/24.
//

#include "UserInterface.h"

void UserInterface::displayCurrentStationInfo(Train train) {
    Direction currentDirection = train.getDirection();

    if (currentDirection == NULL_DIRECTION) {
        // do nothing (the user is not currently on a line)
    } else {
        displayCurrentLineInfo(train);
    }
    cout << "\nCurrent Station:\n" << train.getCurrentStation();
}

void UserInterface::displayCurrentLineInfo(Train train) {
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
        currentLineInfo = currentDirectionLabel + " " + currentLineStr + " Train " + directionArrowSymbol;
    } else {
        currentLineInfo = currentDirectionLabel + " " + currentLineStr + " " + currentLineTypeStr + " Train " + directionArrowSymbol;
    }

    cout << "\n\nCurrent Line:\n\t" << currentLineInfo << endl;
}

void UserInterface::displayDestinationStationInfo(Station destinationStation) {
    cout << "Destination Station:\n" << destinationStation;
}

void UserInterface::announceLastStop(Train &train) {
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

void UserInterface::displayUpcomingStations(Train train) {
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
            } else {
                cout << setw(35) << left << stations[i].getName()
                     << stations[i].getTransferLinesString()
                     << " " << stopsAwayText << endl;
                cout << "    |" << endl;
            }
        }
        cout << "    ↑" << endl;
    } else { // DOWNTOWN
        cout << "    ↓" << endl;
        for (int i = train.getCurrentStationIndex(); i >= 0; i--) {
            int stopsAway = abs(train.getCurrentStationIndex() - i);
            string stopsAwayText = (stopsAway == 0) ? ""
                                                    : (stopsAway == 1) ? "(Next Stop)"
                                                                       : "(" + to_string(stopsAway) + " stops away)";

            if (stations[i].getId() == currentStationID) {
                cout << setw(30) << left << stations[i].getName() << " **  Current Station  **" << endl;
                cout << "    |" << endl;
            } else {
                cout << setw(35) << left << stations[i].getName()
                     << stations[i].getTransferLinesString()
                     << " " << stopsAwayText << endl;
                cout << "    |" << endl;
            }
        }
    }

    cout << "------------------------------------------------------------------" << endl;
}

void UserInterface::displayAllChallenges(Challenge challenge) {
    cout << "\n\t\t\t\t\tStarting Station\t\t\t\t\t\t\t\t\t\t\t\t\t\tDestination Station\t\t\t\t\t\t Difficulty\n" << endl;
    int count = 1;
    for (Challenge c : challenge.getAllChallenges()) {
        cout << count << (count < 10 ? ":  " : ": ") << c << endl;
        ++count;
    }
    cout << count << ": New Custom Journey..." << endl;
}

void UserInterface::displayStationsFor(vector<Station> stations) {
    cout << "  ID  |         Station Name         |\n";
    cout << "------|------------------------------|\n";
    for (auto it = stations.rbegin(); it != stations.rend(); ++it) {
        Station station = *it;
        cout << " " << station.getId() << "  |  " << station.getName() << endl;
    }
}

void UserInterface::displayGameWin(Train train, GameStats stats) {
    cout << "\nYour current Station:\n" << train.getCurrentStation();
    cout << "\nYOU WIN\n\n";
    cout << stats << endl;
}

void UserInterface::displayTransferSuccess(Train train) {
    cout << "Successfully transferred to the " << Line::getTextForEnum(train.getLine()) << " train platform." << endl;
}

void UserInterface::displayAvailableTrainActions(Train train, GameState gameState) {
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
}

void UserInterface::displayGameReset() {
    cout << "\n\n\n\n-----------GAME RESET-----------\n\n\n\n";
}

void UserInterface::displayDirectionChange(Train train) {
    string trackLabel = Train::getTextForDirectionEnum(train.getDirection(), train.getLine());
    cout << "\nYou switched to the " << trackLabel << " platform." << endl;
}
