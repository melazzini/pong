#pragma once

struct Drawable;

struct IRenderer
{
    virtual void render(Drawable *) = 0;
};

struct IDrawablePrimitive
{
    virtual void paintWithIRenderer(IRenderer *) = 0;
};

class Drawable
{
  public:
    Drawable(IDrawablePrimitive *primitive) : m_primitive{primitive}
    {
    }
    virtual void paint(IRenderer *renderer)
    {
        m_primitive->paintWithIRenderer(renderer);
    }

    virtual void draw() = 0;

    virtual ~Drawable()
    {
    }

  protected:
    IDrawablePrimitive *m_primitive;
};

