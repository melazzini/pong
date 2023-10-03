#pragma once
#include "IPrimitives.h"
#include <SDL2/SDL.h>
#include <memory>

using RendererBackendSDL = std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)>;
struct RendererPrimitiveSDL : IRendererPrimitive
{
    RendererPrimitiveSDL(SDL_Window *wnd);
    RendererBackendSDL m_renderer;

  private:
    RendererBackendSDL makeUniqueRenderer(SDL_Window *wnd);
};
