#include "Game.h"

int main()
{
    auto game{Game::getInstance()};
    game->initialize();
    while (game->isRunning())
    {
        game->handleInput();
        game->update();
        game->output();
    }
    game->destroy();
    return 0;
}
