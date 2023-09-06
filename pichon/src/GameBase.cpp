#include "GameBase.h"
#include <iostream>

GameBase::GameBase(GameBackend *backend) : m_backend(backend), m_running(false)
{
}

bool GameBase::initialize()
{
    if (!loadGameObjects())
    {
        return false;
    }
    m_running = true;
    return true;
}

void GameBase::handleInput()
{
    m_backend->eventManager->pollEvents();
}

void GameBase::update()
{
    auto deltatime{(m_backend->timer != nullptr) ? m_backend->timer->sencondsSinceRestared() : 0.0};
    for (auto manager : m_managers)
    {
        manager->update(deltatime);
    }
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

bool GameBase::addGameObject(std::unique_ptr<GameObject> gameObject, std::string gameObectTag)
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
bool GameBase::hasGameObject(std::string_view tag) const
{
    if (auto itr{std::find_if(std::begin(m_gameObjects), std::end(m_gameObjects),
                              [tag](const auto &gameObject) { return gameObject.second == tag; })};
        itr != std::end(m_gameObjects))
    {
        return true;
    }
    return false;
}

bool GameBase::hasComponentManager(ComponentManager *manager) const
{
    if (auto itr{std::find(std::begin(m_managers), std::end(m_managers), manager)}; itr != std::end(m_managers))
    {
        return true;
    }
    return false;
}
