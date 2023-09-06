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

bool GameBase::initialize()
{
    if (!loadGameObjects())
    {
        return false;
    }
    return true;
}

void GameBase::handleInput()
{
}

void GameBase::update()
{
}

void GameBase::output()
{
    m_backend->window->clear(glm::u8vec4{});

    m_backend->window->present();
}

void GameBase::destroy()
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
        m_managers.insert(component->manager());
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

bool Game::hasComponentManager(ComponentManager *manager) const
{

    if (auto itr{std::find(std::begin(m_managers), std::end(m_managers), manager)}; itr != std::end(m_managers))
    {
        return true;
    }
    return false;
}
