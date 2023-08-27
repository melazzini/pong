#pragma once

#include "Drawable.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL_rect.h>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>

struct RenderEngineSDL
{
    SDL_Window *wnd;
};

class BoxDrawablePrimitiveSDL2;
struct RendererSDL : IRenderer
{
    using RendererPrimitiveSDL = std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)>;
    static RendererSDL *getInstance(RenderEngineSDL *engine)
    {
        static RendererSDL renderer(engine->wnd);
        return &renderer;
    }
    virtual void render(Drawable *drawable) override
    {
        drawable->draw();
        drawable->paint(this);
    }

    friend BoxDrawablePrimitiveSDL2;

    RendererPrimitiveSDL m_renderer;

  private:
    RendererSDL(SDL_Window *wnd) : m_renderer(makeUniqueRenderer(wnd))
    {
    }

    RendererPrimitiveSDL makeUniqueRenderer(SDL_Window *wnd)
    {
        auto r{SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED)};
        if (r == nullptr)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return RendererPrimitiveSDL{r, [](SDL_Renderer *_r) {
                                        if (_r)
                                        {
                                            SDL_DestroyRenderer(_r);
                                        }
                                    }};
    }
};

struct BoxDrawablePrimitive : IDrawablePrimitive
{
    glm::ivec2 position;
    glm::ivec2 size;
    glm::ivec4 color;

    void paintWithIRenderer(IRenderer *renderer) override;
};

