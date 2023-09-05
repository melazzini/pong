#include "Game.h"
#include "pong/Ball.h"
#include "pong/Paddle.h"
#include <iostream>

int main()
{
    auto game{Game::getInstance()};
    if (!game->initialize())
    {
        std::cerr << "Error while initializing the game!" << std::endl;
        return -1;
    }
    if (!game->addGameObject(std::make_unique<Paddle>(), "player"))
    {
        return -1;
    }
    if (!game->addGameObject(std::make_unique<Ball>(), "ball"))
    {
        return -1;
    }

    while (game->isRunning())
    {
        game->handleInput();
        game->update();
        game->output();
    }
    game->destroy();
    return 0;
}
