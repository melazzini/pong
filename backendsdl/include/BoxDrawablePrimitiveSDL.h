#pragma once
#include "IPrimitives.h"
#include "Interfaces.h"
#include <glm/glm.hpp>

struct SDL_Renderer;
struct RendererPrimitiveSDL;

class DrawablePrimitiveSDL : IDrawablePrimitive
{
  protected:
    SDL_Renderer *provideRendererSDL(RendererPrimitiveSDL *rendererPrimitive) const;
};

struct BoxDrawablePrimitiveSDL : IDrawablePrimitive
{
    glm::u8vec4 color;
    glm::ivec2 position;
    glm::ivec2 size;

    void paintWithRendererPrimitive(IRendererPrimitive *) override;

    glm::u8vec4 getBackgroundColor() const override
    {
        return color;
    }

    void setBackgroundColor(glm::u8vec4 newColor) override
    {
        color = newColor;
    }
};

