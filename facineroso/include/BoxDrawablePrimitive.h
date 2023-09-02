#pragma once
#include "Interfaces.h"

#include <glm/glm.hpp>

struct BoxDrawablePrimitive : IDrawablePrimitive
{
    glm::u8vec4 color;
    glm::ivec2 position;
    glm::ivec2 size;

    void paintWithRendererPrimitive(IRendererPrimitive *) override;
};

