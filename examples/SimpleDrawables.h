/*
 * This example shows the idea of how to create drawables using the facineroso api
 * and a custom backend, which in this case is based on sdl
 */
#pragma once
#include "../backendsdl/include/BoxDrawablePrimitiveSDL.h"
#include "../facineroso/include/Box.h"

struct Paddle : Box
{
    Paddle(glm::ivec2 position, RectangularGeometry size)
        : Box(position, size, std::make_unique<BoxDrawablePrimitiveSDL>()),
          m_boxDrawablePrimitive(dynamic_cast<BoxDrawablePrimitiveSDL *>(m_primitive.get()))
    {
    }

    void draw() override
    {
        m_boxDrawablePrimitive->position = position();
        m_boxDrawablePrimitive->size = {width(), height()};
        m_boxDrawablePrimitive->color = {255, 100, 244, 255};
    }

  private:
    BoxDrawablePrimitiveSDL *m_boxDrawablePrimitive;
};

struct Ball : Box
{
    Ball(glm::ivec2 position, int size)
        : Box(position, RectangularGeometry{size, size}, std::make_unique<BoxDrawablePrimitiveSDL>()),
          m_boxDrawablePrimitive(dynamic_cast<BoxDrawablePrimitiveSDL *>(m_primitive.get()))
    {
    }

    void draw() override
    {
        m_boxDrawablePrimitive->position = position();
        m_boxDrawablePrimitive->size = {width(), height()};
        m_boxDrawablePrimitive->color = {255, 0, 0, 255};
    }

  private:
    BoxDrawablePrimitiveSDL *m_boxDrawablePrimitive;
};
