#include "Game.h"
#include <iostream>

Game *Game::getInstance()
{
    static Game game{WINDOW_SIZE};
    return &game;
}

Game::Game(RectangularGeometry windowSize) : m_running{false}, m_windowSize{windowSize}
{
    std::cout << "Creating the game..." << std::endl;
}

bool Game::initialize()
{
    loadGameObjects();
    return false;
}

void Game::handleInput()
{
}

void Game::update()
{
}

void Game::output()
{
}

void Game::destroy()
{
    std::cout << "Bye!" << std::endl;
}
