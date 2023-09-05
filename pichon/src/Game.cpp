#include "Game.h"

Game *Game::getInstance()
{
    static Game game{WINDOW_SIZE};
    return &game;
}

Game::Game(RectangularGeometry windowSize) : m_running{false}, m_windowSize{windowSize}
{
}

bool Game::initialize()
{
    // loadGameObjects();
    return false;
}

