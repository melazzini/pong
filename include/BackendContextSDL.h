#pragma once
#include "Interfaces.h"
#include <SDL2/SDL.h>
#include <memory>

struct BackendContextSDL : IBackendContext
{
    inline static SDL_Window *wnd{};
    inline static SDL_Renderer *renderer{};

    std::unique_ptr<IRendererPrimitive> rendererPrimitive() override
    {
        auto rendererPrimitive{std::make_unique<RendererPrimitive>(wnd)};
        renderer = rendererPrimitive->m_renderer.get();
        return rendererPrimitive;
    }

    using RendererBackendSDL = std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)>;
    struct RendererPrimitive : IRendererPrimitive
    {
        RendererBackendSDL m_renderer;
        RendererPrimitive(SDL_Window *wnd) : m_renderer(makeUniqueRenderer(wnd))
        {
        }

      private:
        RendererBackendSDL makeUniqueRenderer(SDL_Window *wnd)
        {
            auto r{SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED)};
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
    };
};
