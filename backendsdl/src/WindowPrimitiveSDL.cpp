#include "WindowPrimitiveSDL.h"
#include "BackendContextSDL.h"
#include <SDL.h>

WindowPrimitive::WindowPrimitive() : m_window{makeUniqueWindow()}
{
}

void WindowPrimitive::clearWindow(glm::u8vec4 color)
{
    SDL_SetRenderDrawColor(BackendContextSDL::renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(BackendContextSDL::renderer);
}

void WindowPrimitive::updateWindow()
{
    SDL_RenderPresent(BackendContextSDL::renderer);
}

WindowBackendSDL WindowPrimitive::makeUniqueWindow()
{
    auto wnd{
        SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_OPENGL)};
    if (wnd == nullptr)
    {
        throw std::runtime_error{SDL_GetError()};
    }
    return WindowBackendSDL{wnd, [](SDL_Window *_w) {
                                if (_w)
                                {
                                    SDL_DestroyWindow(_w);
                                }
                            }};
}
