#include "Game.h"

int main(int argc, char* argv[]) {
    Game game;
    UserPrompt prompt;
    do {
        game.startGame(argc, argv);
    } while (prompt.promptToPlayAgain());

    return 0;
}
