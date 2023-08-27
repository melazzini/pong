#include "Interfaces.h"
#include "RendererPrimitive.h"
#include "RendererSDL.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using testing::Eq;
using testing::Ne;

BackendContext engine;
TEST(ARenderer, IsObtainedWithARenderEngine)
{
    RendererSDL *renderer{RendererSDL::getInstance(&engine)};
}

struct TheRendererSDL : testing::Test
{
    struct DummyDrawable : Drawable
    {
        DummyDrawable(std::unique_ptr<IDrawablePrimitive> primitive) : Drawable(std::move(primitive))
        {
        }
        void draw() override
        {
        }

        MOCK_METHOD(void, paint, (IRenderer *), (override));
    };

    struct DummyDrawablePrimitive : IDrawablePrimitive
    {
        void paintWithRendererPrimitive(IRendererPrimitive *) override
        {
        }
    };

    std::unique_ptr<DummyDrawable> drawable{};
    RendererSDL *renderer{RendererSDL::getInstance(&engine)};

    void SetUp() override
    {
        drawable = std::make_unique<DummyDrawable>(std::make_unique<DummyDrawablePrimitive>());
    }
};

TEST_F(TheRendererSDL, DISABLED_PassesItselfToTheDrawableForPainting)
{
    EXPECT_CALL(*(drawable.get()), paint(renderer));
    renderer->render(drawable.get());
}
