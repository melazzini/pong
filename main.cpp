#include "include/Box.h"
#include "include/RendererSDL.h"

#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <glm/fwd.hpp>
#include <iostream>
using namespace std;

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cerr << SDL_GetError() << endl;
        abort();
    }

    auto wnd =
        SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_ALWAYS_ON_TOP);

    if (wnd == nullptr)
    {
        cerr << SDL_GetError() << endl;
        abort();
    }

    RenderEngineSDL engine{wnd};

    auto rendererSDL{RendererSDL::getInstance(&engine)};

    auto renderer{rendererSDL->m_renderer.get()};

    Paddle paddle{};
    paddle.resize(20, 100);

    Ball ball{};
    ball.resize(40, 40);

    ball.setPosition(glm::ivec2{300, 300});

    if (renderer == nullptr)
    {
        cerr << SDL_GetError() << endl;
        abort();
    }

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

        SDL_SetRenderDrawColor(renderer, 101, 101, 130, 255);
        SDL_RenderClear(renderer);

        rendererSDL->render(&paddle);
        rendererSDL->render(&ball);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(wnd);
    SDL_Quit();
    cout << "Hello world!" << endl;

    return 0;
}
