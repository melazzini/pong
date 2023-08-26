#include "Drawable.h"
#include "RendererSDL.h"

#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using testing::Eq;
using testing::Ne;

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

        MOCK_METHOD(void, paint, (IRenderer *), (override));
    };

    struct DummyDrawablePrimitive : IDrawablePrimitive
    {
        void paintWithIRenderer(IRenderer *) override
        {
        }
    };

    DummyDrawablePrimitive drawablePrimitive;

    std::unique_ptr<DummyDrawable> drawable{};

    void SetUp() override
    {
        drawable = std::make_unique<DummyDrawable>(&drawablePrimitive);
    }
};

TEST_F(TheRendererSDL, PassesItselfToTheDrawableForPainting)
{
    RendererSDL *renderer{RendererSDL::getInstance()};

    EXPECT_CALL(*(drawable.get()), paint(renderer));

    renderer->render(drawable.get());
}
