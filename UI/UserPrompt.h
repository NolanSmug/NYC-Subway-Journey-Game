//
// Created by Nolan Cyr on 5/18/24.
//

#ifndef NYC_SUBWAY_JOURNEY_GAME_USERPROMPT_H
#define NYC_SUBWAY_JOURNEY_GAME_USERPROMPT_H

#include "../../Game/GameState/GameState.h"
#include "../../Game/Challenge/Challenge.h"
#include "../../Core/Train/Train.h"
#include "../UserInterface/UserInterface.h"
#include "../../Core/Line/Line.h"

#include <iostream>

class UserInterface;

enum InputAction {
    RESET_GAME,
    ADVANCE_STATION,
    ADVANCE_NUM_STATION,
    TRANSFER_LINE,
    CHANGE_DIRECTION,
    DISPLAY_DESTINATION,
    DISPLAY_UPCOMING_STATIONS,
    INVALID
};

class UserPrompt {
public:
    void promptForGameMode(GameState& gameState);
    static bool promptToPlayAgain();

    void promptForChallengeSelection(GameState& gameState);
    void promptsForCustomChallenge(Challenge& challenge);
    LineName promptLineSelection(bool isStartingStation);
    Station promptStationFromLine(LineName line, bool isStartingStation);

    void promptForStartingLine(Train& train);
    void promptForDirection(Train& train);
    void promptForAtRockawayBranch(Train& train, GameState& gameState);
    bool promptForTransfer(Train& train);

    InputAction parseInputToInputAction(string input);
    string getInput();

private:
    UserInterface uiPrompt;

    bool isnumber(const string &s);
};


#endif //NYC_SUBWAY_JOURNEY_GAME_USERPROMPT_H
