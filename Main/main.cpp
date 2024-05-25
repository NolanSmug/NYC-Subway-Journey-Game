#include "../Core/GameLogic/Game.h"


int main(int argc, char* argv[]) {
    Game game;
    game.initializeArgs(argc, argv);

    do {
        game.runGame();
    } while (UserPrompt::promptToPlayAgain());

    return 0;
}
