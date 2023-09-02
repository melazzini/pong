#include "BackendContextSDL.h"
#include "Box.h"
#include "EventManager.h"
#include "Interfaces.h"
#include "Renderer.h"
#include "Window.h"
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

    auto lambdaEventHnd = eventManager->registerListener(
        EventType::QUIT, [](const IEvent &event) { std::cout << "Oh YEAH!!!! :)))))" << std::endl; });

    auto moveBallEventHandler{
        eventManager->registerListener(EventType::ARROW_KEYS_PRESSED, [&ball](const IEvent &event) {
            const ArrowKeyPressed &arrowEvent{dynamic_cast<const ArrowKeyPressed &>(event)};
            if (arrowEvent.key() == ArrowKey::RIGHT)
            {
                glm::ivec2 pos{ball.position().x + 10, ball.position().y};
                ball.setPosition(pos);
            }
            if (arrowEvent.key() == ArrowKey::LEFT)
            {
                glm::ivec2 pos{ball.position().x - 10, ball.position().y};
                ball.setPosition(pos);
            }
            if (arrowEvent.key() == ArrowKey::UP)
            {
                glm::ivec2 pos{ball.position().x, ball.position().y - 10};
                ball.setPosition(pos);
            }
            if (arrowEvent.key() == ArrowKey::DOWN)
            {
                glm::ivec2 pos{ball.position().x, ball.position().y + 10};
                ball.setPosition(pos);
            }
        })};

    while (isRunning)
    {
        eventManager->pollEvents();
        window->clear(glm::u8vec4{100, 100, 100, 255});
        rendererSDL->render(&paddle);
        rendererSDL->render(&ball);
        window->present();
    }

    SDL_Quit();
    cout << "Hello world!" << endl;

    return 0;
}
