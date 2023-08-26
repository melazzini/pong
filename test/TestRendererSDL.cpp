#include "Drawable.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using testing::Eq;
using testing::Ne;

struct RendererSDL : IRenderer
{
    static RendererSDL *getInstance()
    {
        static RendererSDL renderer;
        return &renderer;
    }
    virtual void render(Drawable *) override
    {
    }

  private:
    RendererSDL() = default;
};

struct TheRendererSDL : testing::Test
{
    struct DummyDrawable : Drawable
    {
        DummyDrawable(IDrawablePrimitive *primitive) : Drawable(primitive)
        {
        }
        void draw() override
        {
        }
    };

    struct DummyDrawablePrimitive : IDrawablePrimitive
    {
        void paintWithIRenderer(IRenderer *) override
        {
        }
    };

    DummyDrawablePrimitive drawablePrimitive;

    std::unique_ptr<Drawable> drawable{};

    void SetUp() override
    {
        drawable = std::make_unique<DummyDrawable>(&drawablePrimitive);
    }
};

TEST_F(TheRendererSDL, CanRenderADrawable)
{
    RendererSDL *renderer{RendererSDL::getInstance()};
    renderer->render(drawable.get());
}
