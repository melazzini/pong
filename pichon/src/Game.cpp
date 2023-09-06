#include "Game.h"
#include <iostream>
#include <iterator>
#include <memory>

Game *Game::getInstance(Game::GameBackend *backend)
{
    if (!backend)
    {
        return nullptr;
    }
    static Game game{backend, WINDOW_SIZE};
    return &game;
}

Game::Game(Game::GameBackend *backend, RectangularGeometry windowSize) : GameBase(backend), m_windowSize{windowSize}
{
    std::cout << "Creating the game..." << std::endl;
}

