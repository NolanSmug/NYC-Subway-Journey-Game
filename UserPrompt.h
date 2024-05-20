//
// Created by Nolan Cyr on 5/18/24.
//

#ifndef NYC_SUBWAY_JOURNEY_GAME_USERPROMPT_H
#define NYC_SUBWAY_JOURNEY_GAME_USERPROMPT_H

#include "Game.h"

class UserPrompt {
public:
    /******************** Prompting for Game Setup ********************/
    void promptForGameMode(GameState& gameState);
    static bool promptToPlayAgain();

    /**************** Prompting for Challenge Setup *******************/
    void promptForChallengeSelection(GameState& gameState);
    void promptsForCustomChallenge(Challenge& challenge);
    LineName promptLineSelection(bool isStartingStation);
    Station promptStationFromLine(LineName line, bool isStartingStation);

    /******************* Prompting for Train Actions ********************/
    void promptForStartingLine(Train& train);
    void promptForDirection(Train& train);
    void promptForAtRockawayBranch(Train& train, GameState& gameState);
    bool promptForTransfer(Train& train);


    string getInput(Train &train, GameState &gameState);


private:
    bool isnumber(const string &s);
};


#endif //NYC_SUBWAY_JOURNEY_GAME_USERPROMPT_H
