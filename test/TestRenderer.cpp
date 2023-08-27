#include "Drawable.h"
#include "Interfaces.h"
#include "Renderer.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using testing::Eq;
using testing::Ne;

struct DummyRendererPrimitive : IRendererPrimitive
{
};

struct DummyBackendContext : IBackendContext
{
    std::unique_ptr<IRendererPrimitive> rendererPrimitive() override
    {
        return std::make_unique<DummyRendererPrimitive>();
    }
};

DummyBackendContext engine;
TEST(ARenderer, IsASingleton)
{
    Renderer *renderer1{Renderer::getInstance(&engine)};
    Renderer *renderer2{Renderer::getInstance(&engine)};
    ASSERT_THAT(renderer1, Eq(renderer2));
}

struct TheRenderer : testing::Test
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
    Renderer *renderer{Renderer::getInstance(&engine)};

    void SetUp() override
    {
        drawable = std::make_unique<DummyDrawable>(std::make_unique<DummyDrawablePrimitive>());
    }
};

TEST_F(TheRenderer, PassesItselfToTheDrawableForPainting)
{
    EXPECT_CALL(*(drawable.get()), paint(renderer));
    renderer->render(drawable.get());
}
