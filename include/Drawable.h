#pragma once

struct Renderer
{
};

struct DrawablePrimitive
{
    virtual void paintWithRenderer(Renderer *)
    {
    }

    virtual ~DrawablePrimitive()
    {
    }
};

class Drawable
{
  public:
    Drawable(DrawablePrimitive *primitive) : m_primitive{primitive}
    {
    }
    void paint(Renderer *renderer)
    {
        m_primitive->paintWithRenderer(renderer);
    }

    virtual void draw() = 0;

    virtual ~Drawable()
    {
    }

  protected:
    DrawablePrimitive *m_primitive;
};

