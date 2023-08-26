#include "include/RendererSDL.h"

#include <SDL2/SDL.h>
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

    auto renderer = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_SOFTWARE);

    if (renderer == nullptr)
    {
        cerr << SDL_GetError() << endl;
        abort();
    }

    SDL_Rect rect;
    rect.h = 40;
    rect.w = 40;
    rect.x = rect.y = 30;

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
        }

        SDL_SetRenderDrawColor(renderer, 101, 101, 130, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 200, 201, 10, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(wnd);
    SDL_Quit();
    cout << "Hello world!" << endl;

    return 0;
}
