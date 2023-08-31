#pragma once

#include "Interfaces.h"

class Drawable
{
  public:
    Drawable(std::unique_ptr<IDrawablePrimitive> primitive) : m_primitive{std::move(primitive)}
    {
    }
    virtual void paint(IRenderer *renderer)
    {
        m_primitive->paintWithRendererPrimitive(renderer->primitive());
    }

    virtual void draw() = 0;

    virtual ~Drawable() = default;

  protected:
    std::unique_ptr<IDrawablePrimitive> m_primitive;
};

