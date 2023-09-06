#include "../../backendsdl/include/BackendContextSDL.h"
#include "EventManager.h"
#include "Game.h"
#include "Interfaces.h"
#include "Renderer.h"
#include "Window.h"
#include "pong/Ball.h"
#include "pong/Paddle.h"
#include <iostream>
#include <memory>

int main()
{
    auto engine{BackendContextSDL::getInstance()};
    auto window = Window::getInstance(engine);
    auto backendEventMangerPrimitiveProdiver{EventManagerPrimitiveProviderSDL()};
    auto eventManager{EventManager::getInstance(&backendEventMangerPrimitiveProdiver)};
    auto rendererSDL{Renderer::getInstance(engine)};

    Game::GameBackend backend{window, rendererSDL, eventManager};
    auto game{Game::getInstance(&backend)};
    if (!game)
    {
        std::cerr << "Error while initializing the game!" << std::endl;
        return -1;
    }
    if (!game->addGameObject(std::make_unique<Paddle>(eventManager), "player"))
    {
        return -1;
    }
    if (!game->addGameObject(std::make_unique<Ball>(), "ball"))
    {
        return -1;
    }

    while (game->isRunning())
    {
        game->handleInput();
        game->update();
        game->output();
    }
    game->destroy();
    return 0;
}
