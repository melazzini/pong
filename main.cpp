#include "include/BackendContextSDL.h"
#include "include/Box.h"
#include "include/EventManager.h"
#include "include/Interfaces.h"
#include "include/Renderer.h"
#include "include/Window.h"
#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <glm/fwd.hpp>
#include <iostream>
#include <memory>
using namespace std;

auto isRunning = true;

struct QuitEventListener : IListener
{
    void onEvent(const IEvent &event) override
    {
        std::cout << __FUNCTION__ << std::endl;
        std::cout << "Bye!" << std::endl;
        isRunning = false;
    }

    EventType eventType() const override
    {
        return EventType::QUIT;
    }
    ~QuitEventListener() = default;
};

int main()
{
    auto engine{BackendContextSDL::getInstance()};
    auto window = Window::getInstance(engine);
    auto backendEventMangerPrimitiveProdiver{EventManagerPrimitiveProviderSDL()};
    auto eventManager{EventManager::getInstance(&backendEventMangerPrimitiveProdiver)};

    auto rendererSDL{Renderer::getInstance(engine)};

    Paddle paddle{};
    paddle.resize(20, 100);

    Ball ball{};
    ball.resize(40, 40);

    ball.setPosition(glm::ivec2{300, 300});

    auto quitEventListener{std::make_unique<QuitEventListener>()};

    eventManager->registerListener(quitEventListener.get());

    while (isRunning)
    {
        eventManager->pollEvents();
        eventManager->dispatchEvents();

        window->clear(glm::u8vec4{100, 100, 100, 255});

        rendererSDL->render(&paddle);
        rendererSDL->render(&ball);

        window->present();
    }

    SDL_Quit();
    cout << "Hello world!" << endl;

    return 0;
}
