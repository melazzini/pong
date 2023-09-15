#include "../../backendsdl/include/BackendContextSDL.h"
#include "EventManager.h"
#include "Game.h"
#include "GameBase.h"
#include "Interfaces.h"
#include "Renderer.h"
#include "Window.h"
#include "pong/Ball.h"
#include "pong/Paddle.h"
#include "pong/Wall.h"
#include <bits/chrono.h>
#include <chrono>
#include <iostream>
#include <memory>

extern GameBase *gameInstance;

int main()
{
    auto engine{BackendContextSDL::getInstance()};
    auto window = Window::getInstance(engine);
    auto backendEventMangerPrimitiveProdiver{EventManagerPrimitiveProviderSDL()};
    auto eventManager{EventManager::getInstance(&backendEventMangerPrimitiveProdiver)};
    auto rendererSDL{Renderer::getInstance(engine)};

    Game::GameBackend backend{window, rendererSDL, eventManager};
    auto game{Game::getInstance(&backend)};
    gameInstance = game;
    if (!game)
    {
        std::cerr << "Error while initializing the game!" << std::endl;
        return -1;
    }
    if (!game->addGameObject(std::make_unique<Paddle>(eventManager, rendererSDL), "player"))
    {
        return -1;
    }
    if (!game->addGameObject(std::make_unique<Ball>(rendererSDL), "ball"))
    {
        return -1;
    }
    if (!game->addGameObject(
            std::make_unique<Wall>(rendererSDL, glm::ivec2(0, 0), RectangularGeometry{800, 20}, "TopWall"), "TopWall"))
    {
        return -1;
    }
    if (!game->addGameObject(
            std::make_unique<Wall>(rendererSDL, glm::ivec2(0, 780), RectangularGeometry{800, 20}, "BottomWall"),
            "BottomWall"))
    {
        return -1;
    }
    if (!game->addGameObject(
            std::make_unique<Wall>(rendererSDL, glm::ivec2(780, 0), RectangularGeometry{20, 800}, "RightWall"),
            "RightWall"))
    {
        return -1;
    }
    while (game->isRunning())
    {
        //    auto start = std::chrono::high_resolution_clock::now();
        game->handleInput();
        game->update();
        game->output();
        //   auto end = std::chrono::high_resolution_clock::now();
        //  std::cout << "cycle lasted: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        //           << "ms" << std::endl;
    }
    game->destroy();
    return 0;
}
