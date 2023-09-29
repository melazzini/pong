#include "Game.h"
#include "EventManagementInterface.h"
#include "EventManager.h"
#include "EventUtils.h"
#include "GameInterfaces.h"
#include "GameLoop.h"
#include "GameObjectsManager.h"
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>

struct Game::_Pimpl
{
    GameLoop *m_gameLoop;
    GameObjetctsManager *m_gameObjectsManager;
};

int Game::launchGame()
{
    if (!m_pimpl->m_gameLoop->initialize())
    {
        throw std::runtime_error{"Error while launching the game"};
    }

    while (m_pimpl->m_gameLoop->running)
    {
        m_pimpl->m_gameLoop->handleInput();
        // m_pimpl->m_gameLoop->update();
        //        m_pimpl->m_gameLoop->output();
    }

    m_pimpl->m_gameLoop->destroy();

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

