#pragma once

struct Drawable;

struct IRenderer
{
    // this code has not yet being tested and it's just for ilustration
    // virtual void render(Drawable *) = 0;
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
    void paint(IRenderer *renderer)
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

// The next code is just for ilustration and has not being tested.
// THIS IS THE CONCRETE IMPLEMENTATION
// WHICH CAN BE A SINGLETON
struct Renderer : IRenderer
{
    static Renderer *getInstance()
    {
        return nullptr;
    }
    // virtual void render(Drawable *) override
    //{
    // }

  private:
    Renderer() = default;
};
