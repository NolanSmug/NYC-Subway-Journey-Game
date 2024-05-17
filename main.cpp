#include "Game.h"

int main(int argc, char* argv[]) {
    Game game;
    do {
        game.startGame(argc, argv);
    } while (game.promptToPlayAgain());

    return 0;
}
