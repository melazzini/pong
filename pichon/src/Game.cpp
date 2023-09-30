#include "Game.h"
#include "EventManagementInterface.h"
#include "EventManager.h"
#include "EventUtils.h"
#include "GameInterfaces.h"
#include "GameLoop.h"
#include "GameObject.h"
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
           std::chrono::milliseconds frameDuration, IEventManager *eventManager, IWindow *window)
        : m_gameLoop{std::move(gameLoop)}, m_gameObjectsManager{std::move(gameObjectsManager)}, m_ticker{frameDuration},
          m_eventManager{eventManager}, m_window{window}, m_gameRunning{false}
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
        m_window->clear(glm::u8vec4{0, 0, 255, 255});
        m_gameLoop->generateOutput(m_gameObjectsManager.get());
        m_window->present();
    }

    void destroy()
    {
        m_gameLoop->destroy(m_gameObjectsManager.get());
    }

    bool addGameObject(std::unique_ptr<GameObject> gameobj, const std::string &tag)
    {
        return m_gameObjectsManager->addGameObject(std::move(gameobj), tag);
    }

    void setRunning(bool trueFalse)
    {
        m_gameRunning = trueFalse;
    }

  private:
    std::unique_ptr<IGameLoop> m_gameLoop;
    std::unique_ptr<IGameObjectsManager> m_gameObjectsManager;
    SimpleTicker m_ticker;
    IEventManager *m_eventManager;
    IWindow *m_window;
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

bool Game::addGameObject(std::unique_ptr<GameObject> gameobj, const std::string &tag)
{
    return m_pimpl->addGameObject(std::move(gameobj), tag);
}

void Game::terminate()
{
    m_pimpl->setRunning(false);
}

Game::Game(Game::GameBackend *backend, RectangularGeometry windowSize) : m_windowSize{windowSize}, m_backend{backend}
{
    std::cout << "Creating the game..." << std::endl;
    static CallbackEventListener listener{EventType::QUIT,
                                          [this](const IEvent &) { this->m_pimpl->setRunning(false); }};
    if (m_backend->eventManager)
    {
        m_backend->eventManager->registerListener(&listener);
    }

    m_pimpl = new _Pimpl(std::make_unique<GameLoop>(), std::make_unique<GameObjectsManager>(),
                         std::chrono::milliseconds(15), m_backend->eventManager, m_backend->window);
}

