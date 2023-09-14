#include "GameBase.h"
#include "components/DrawableComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <chrono>
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

static float deltatime_;

static const uint32_t TicksPerFrame{17};
static uint32_t ticksPrevFrame{};

void GameBase::update()
{
    auto ticksThisFrame = SDL_GetTicks();
    // deltatime_ = (m_backend->timer != nullptr) ? m_backend->timer->sencondsSinceRestared() : 0.0;
    auto dTicks{ticksThisFrame - ticksPrevFrame};
    ticksPrevFrame = ticksThisFrame;

    if (dTicks < TicksPerFrame)
    {
        SDL_Delay(TicksPerFrame - dTicks);
    }

    for (auto manager : m_managers)
    {
        manager->update(TicksPerFrame);
    }
}

void GameBase::output()
{
    m_backend->window->clear(glm::u8vec4{});
    for (auto manager : m_managers)
    {
        if (auto drawableManager = dynamic_cast<DrawableComponentManagerBase *>(manager); drawableManager)
        {
            drawableManager->paintComponents();
        }
    }
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

    gameObject->setName(gameObectTag);
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
