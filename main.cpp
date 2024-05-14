#include "Game.h"

int main(int argc, char* argv[]) {
    Game game;
    bool userWantsToPlay;

    do {
        game.startGame(argc, argv);
        userWantsToPlay = game.promptToPlayAgain();
    } while (userWantsToPlay);

    return 0;
}
