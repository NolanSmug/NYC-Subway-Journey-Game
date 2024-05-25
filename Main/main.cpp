#include "../Core/Game/Game.h"

int main(int argc, char* argv[]) {
    Game game;

    do {
        game.runGame(argc, argv);
    } while (UserPrompt::promptToPlayAgain());

    return 0;
}
