#pragma once

#include "Drawable.h"
#include "Interfaces.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <memory>
#include <stdexcept>

struct BackendContext;
struct RendererPrimitive;

struct Renderer : IRenderer
{
    static Renderer *getInstance(BackendContext *engine);
    virtual void render(Drawable *drawable) override;

    IRendererPrimitive *primitive() override;

  private:
    Renderer(BackendContext *);
    std::unique_ptr<RendererPrimitive> m_pimpl;
};

