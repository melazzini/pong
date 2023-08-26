#pragma once

#include "Drawable.h"

struct RendererSDL : IRenderer
{
    static RendererSDL *getInstance()
    {
        static RendererSDL renderer;
        return &renderer;
    }
    virtual void render(Drawable *drawable) override
    {
        drawable->paint(this);
    }

  private:
    RendererSDL() = default;
};

