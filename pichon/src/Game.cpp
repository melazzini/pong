#include "Game.h"
#include "EventManagementInterface.h"
#include "EventManager.h"
#include "EventUtils.h"
#include <functional>
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
    initialize();
    static CallbackEventListener listener{EventType::QUIT, [this](const IEvent &) { this->setRunning(false); }};
    if (m_backend->eventManager)
    {
        m_backend->eventManager->registerListener(&listener);
    }
}

