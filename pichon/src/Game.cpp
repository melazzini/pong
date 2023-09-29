#include "Game.h"
#include "EventManagementInterface.h"
#include "EventManager.h"
#include "EventUtils.h"
#include "GameInterfaces.h"
#include "GameLoop.h"
#include "GameObjectsManager.h"
#include "SimpleTicker.h"
#include "components/Component.h"
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <vector>

struct Game::_Pimpl
{
    SimpleTicker ticker{std::chrono::milliseconds(16)};
    GameLoop *m_gameLoop;
    GameObjetctsManager *m_gameObjectsManager;
    std::vector<ComponentManager *> managers;
    std::vector<OutputComponentManager *> outputComponentManagers;

    bool gameRunning() const
    {
        return m_gameLoop->running;
    }

    void initialize()
    {
        if (!m_gameLoop->initialize())
        {
            throw std::runtime_error{"Error while launching the game"};
        }
    }

    void handleInput()
    {
        m_gameLoop->handleInput();
    }
    void update()
    {
        auto deltatime = ticker.tick().count();
        m_gameLoop->update(deltatime, managers);
    }
    void output()
    {
        m_gameLoop->output(outputComponentManagers);
    }

    void destroy()
    {
        m_gameLoop->destroy(managers);
    }
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

