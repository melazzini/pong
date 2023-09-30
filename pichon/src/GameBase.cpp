#include "GameBase.h"
#include "components/DrawableComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <chrono>
#include <iostream>
#include <thread>

static uint32_t ticksPrevFrame{};
GameBase::GameBase(GameBackend *backend) : m_backend(backend), m_running(false)
{
    ticksPrevFrame = SDL_GetTicks();
}

int GameBase::launch()
{
    while (isRunning())
    {
        handleInput();
        update();
        output();
    }
    destroy();
    return 0;
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

static const uint32_t TicksPerFrame{16};

void GameBase::update()
{
    auto dTime_ms{m_backend->ticker->tick()};

    for (auto manager : m_managers)
    {
        manager->updateComponents(dTime_ms.count());
    }
}

// void GameBase::update()
//{
//     // Wait until 16ms has elapsed since last frame
//     while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksPrevFrame + TicksPerFrame))
//         ;
//     /// Delta time is the difference in ticks from last frame
//     // (converted to seconds)
//     auto deltaTime = SDL_GetTicks() - ticksPrevFrame;
//
//     deltaTime = deltaTime > 3 * TicksPerFrame ? 3 * TicksPerFrame : deltaTime;
//     // Update tick counts (for next frame)
//     ticksPrevFrame = SDL_GetTicks();
//     for (auto manager : m_managers)
//     {
//         manager->update(deltaTime);
//     }
// }

void GameBase::output()
{
    m_backend->window->clear(glm::u8vec4{0, 0, 255, 255});
    for (auto manager : m_managers)
    {
        if (auto drawableManager = dynamic_cast<DrawableComponentManagerBase *>(manager); drawableManager)
        {
            drawableManager->output();
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
