#pragma once

#include "Drawable.h"
#include "Interfaces.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <memory>
#include <stdexcept>

struct IBackendContext;
struct IRendererPrimitive;

struct Renderer : IRenderer
{
    static Renderer *getInstance(IBackendContext *engine);
    virtual void render(Drawable *drawable) override;

    IRendererPrimitive *primitive() override;

  private:
    Renderer(IBackendContext *);
    std::unique_ptr<IRendererPrimitive> m_primitive;
};

