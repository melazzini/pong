#include "Game.h"
#include "EventManagementInterface.h"
#include "EventManager.h"
#include "EventUtils.h"
#include "GameInterfaces.h"
#include "GameLoop.h"
#include "GameObjectsManager.h"
#include "SimpleTicker.h"
#include "components/Component.h"
#include <chrono>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <vector>

class Game::_Pimpl
{
  public:
    _Pimpl(std::unique_ptr<IGameLoop> gameLoop, std::unique_ptr<IGameObjectsManager> gameObjectsManager,
           std::chrono::milliseconds frameDuration, IEventManager *eventManager)
        : m_gameLoop{std::move(gameLoop)}, m_gameObjectsManager{std::move(gameObjectsManager)}, m_ticker{frameDuration},
          m_eventManager{eventManager}, m_gameRunning{false}
    {
    }

    bool gameRunning() const
    {
        return m_gameRunning;
    }

    void initialize()
    {
        if (!m_gameLoop->initialize())
        {
            throw std::runtime_error{"Error while launching the game"};
        }
        m_gameRunning = true;
    }

    void handleInput()
    {
        m_gameLoop->handleInput(m_eventManager);
    }
    void update()
    {
        auto deltatime = m_ticker.tick().count();
        m_gameLoop->update(deltatime, m_gameObjectsManager.get());
    }
    void output()
    {
        m_gameLoop->generateOutput(m_gameObjectsManager.get());
    }

    void destroy()
    {
        m_gameLoop->destroy(m_gameObjectsManager.get());
    }

  private:
    std::unique_ptr<IGameLoop> m_gameLoop;
    std::unique_ptr<IGameObjectsManager> m_gameObjectsManager;
    SimpleTicker m_ticker;
    IEventManager *m_eventManager;
    bool m_gameRunning;
};

int Game::launchGame()
{
    m_pimpl->initialize();
    while (m_pimpl->gameRunning())
    {
        m_pimpl->handleInput();
        m_pimpl->update();
        m_pimpl->output();
    }
    m_pimpl->destroy();
    return 0;
}

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
    initialize();
    static CallbackEventListener listener{EventType::QUIT, [this](const IEvent &) { this->setRunning(false); }};
    if (m_backend->eventManager)
    {
        m_backend->eventManager->registerListener(&listener);
    }
}

