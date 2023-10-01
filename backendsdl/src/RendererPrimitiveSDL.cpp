#include "RendererPrimitiveSDL.h"

RendererPrimitiveSDL::RendererPrimitiveSDL(SDL_Window *wnd) : m_renderer(makeUniqueRenderer(wnd))
{
}

RendererBackendSDL RendererPrimitiveSDL::makeUniqueRenderer(SDL_Window *wnd)
{
    auto r{SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)};
    if (r == nullptr)
    {
        throw std::runtime_error{SDL_GetError()};
    }

    return RendererBackendSDL{r, [](SDL_Renderer *_r) {
                                  if (_r)
                                  {
                                      SDL_DestroyRenderer(_r);
                                  }
                              }};
}
