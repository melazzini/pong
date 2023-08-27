#include "include/BackendContextSDL.h"
#include "include/Box.h"
#include "include/Renderer.h"
#include "include/Window.h"
#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <glm/fwd.hpp>
#include <iostream>
using namespace std;

int main()
{
    auto engine{BackendContextSDL::getInstance()};
    auto window = Window::getInstance(engine);

    auto rendererSDL{Renderer::getInstance(engine)};

    Paddle paddle{};
    paddle.resize(20, 100);

    Ball ball{};
    ball.resize(40, 40);

    ball.setPosition(glm::ivec2{300, 300});

    auto isRunning = true;
    while (isRunning)
    {
        SDL_Event evt;
        while (SDL_PollEvent(&evt))
        {
            if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
            }
            else if (evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                isRunning = false;
            }

            if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_RIGHT)
            {
                glm::ivec2 pos{paddle.position().x + 10, paddle.position().y};
                paddle.setPosition(pos);
            }
            if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_LEFT)
            {
                glm::ivec2 pos{paddle.position().x - 10, paddle.position().y};
                paddle.setPosition(pos);
            }
            if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_UP)
            {
                glm::ivec2 pos{paddle.position().x, paddle.position().y - 10};
                paddle.setPosition(pos);
            }
            if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_DOWN)
            {
                glm::ivec2 pos{paddle.position().x, paddle.position().y + 10};
                paddle.setPosition(pos);
            }
        }

        window->clear(glm::u8vec4{100, 100, 100, 255});

        rendererSDL->render(&paddle);
        rendererSDL->render(&ball);

        window->present();
    }

    SDL_Quit();
    cout << "Hello world!" << endl;

    return 0;
}
