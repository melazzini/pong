#pragma once
#include "BoxDrawablePrimitive.h"
#include "Drawable.h"
#include "Movable.h"
#include "RectangularGeometry.h"

class Box : public Movable, public RectangularGeometry, public Drawable
{
  public:
    Box(glm::ivec2 position, RectangularGeometry size, std::unique_ptr<IDrawablePrimitive> drawablePrimitive)
        : Movable{position}, RectangularGeometry{size}, Drawable{std::move(drawablePrimitive)}
    {
    }

    void draw() override
    {
    }
};

struct Paddle : Box
{
    Paddle()
        : Box(glm::ivec2{}, RectangularGeometry{100, 100}, std::make_unique<BoxDrawablePrimitive>()),
          m_boxDrawablePrimitive(dynamic_cast<BoxDrawablePrimitive *>(m_primitive.get()))
    {
    }

    void draw() override
    {
        m_boxDrawablePrimitive->position = position();
        m_boxDrawablePrimitive->size = {width(), height()};
        m_boxDrawablePrimitive->color = {255, 100, 244, 255};
    }

  private:
    BoxDrawablePrimitive *m_boxDrawablePrimitive;
};

struct Ball : Box
{
    Ball()
        : Box(glm::ivec2{}, RectangularGeometry{100, 100}, std::make_unique<BoxDrawablePrimitive>()),
          m_boxDrawablePrimitive(dynamic_cast<BoxDrawablePrimitive *>(m_primitive.get()))
    {
    }

    void draw() override
    {
        m_boxDrawablePrimitive->position = position();
        m_boxDrawablePrimitive->size = {width(), height()};
        m_boxDrawablePrimitive->color = {255, 0, 0, 255};
    }

  private:
    BoxDrawablePrimitive *m_boxDrawablePrimitive;
};
