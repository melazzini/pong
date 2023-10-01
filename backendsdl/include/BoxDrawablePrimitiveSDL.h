#pragma once
#include "IPrimitives.h"
#include "Interfaces.h"

#include <glm/glm.hpp>

struct BoxDrawablePrimitiveSDL : IDrawablePrimitive
{
    glm::u8vec4 color;
    glm::ivec2 position;
    glm::ivec2 size;

    void paintWithRendererPrimitive(IRendererPrimitive *) override;
};

