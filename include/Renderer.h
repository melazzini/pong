#pragma once

#include "Interfaces.h"

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

