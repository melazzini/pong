#include "Game.h"
#include <iostream>
#include <iterator>
#include <memory>

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
    if (!loadGameObjects())
    {
        return false;
    }
    return true;
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

bool Game::addGameObject(std::unique_ptr<GameObject> gameObject, std::string gameObectTag)
{
    if (gameObject == nullptr)
    {
        return false;
    }

    if (hasGameObject(gameObectTag))
    {
        return false;
    }

    for (auto &component : gameObject->componentList())
    {
        component->manager()->registerComponent(component.get());
    }

    m_gameObjects.push_back({std::move(gameObject), gameObectTag});

    return true;
}

bool Game::hasGameObject(std::string_view tag) const
{
    if (auto itr{std::find_if(std::begin(m_gameObjects), std::end(m_gameObjects),
                              [tag](const auto &gameObject) { return gameObject.second == tag; })};
        itr != std::end(m_gameObjects))
    {
        return true;
    }
    return false;
}
