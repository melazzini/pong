#include "Drawable.h"
#include "IPrimitives.h"
#include "Interfaces.h"
#include "Renderer.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using testing::Eq;
using testing::InSequence;
using testing::Ne;

struct Dummy2RendererPrimitive : IRendererPrimitive
{
};

struct Dummy2BackendContext : IBackendContext
{
    std::unique_ptr<IRendererPrimitive> rendererPrimitive() override
    {
        return std::make_unique<Dummy2RendererPrimitive>();
    }
    std::unique_ptr<IWindowPrimitive> windowPrimitive() override
    {
        return nullptr;
    }
};

static Dummy2BackendContext engine;
TEST(ARenderer, IsASingleton)
{
    Renderer *renderer1{Renderer::getInstance(&engine)};
    Renderer *renderer2{Renderer::getInstance(&engine)};
    ASSERT_THAT(renderer1, Eq(renderer2));
}

struct TheRenderer : testing::Test
{
    struct Dummy2Drawable : Drawable
    {
        Dummy2Drawable(std::unique_ptr<IDrawablePrimitive> primitive) : Drawable(std::move(primitive))
        {
        }
        MOCK_METHOD(void, draw, (), (override));
        MOCK_METHOD(void, paint, (IRenderer *), (override));
    };

    struct Dummy2DrawablePrimitive : IDrawablePrimitive
    {
        void paintWithRendererPrimitive(IRendererPrimitive *) override
        {
        }
    };

    std::unique_ptr<testing::NiceMock<Dummy2Drawable>> drawable{};
    Renderer *renderer{Renderer::getInstance(&engine)};

    void SetUp() override
    {
        drawable = std::make_unique<testing::NiceMock<Dummy2Drawable>>(std::make_unique<Dummy2DrawablePrimitive>());
    }
};

TEST_F(TheRenderer, RendersTheDrawableFirstMakingItDrawAnThenPaintItSelf)
{
    InSequence s;
    EXPECT_CALL(*(drawable.get()), draw);
    EXPECT_CALL(*(drawable.get()), paint);
    renderer->render(drawable.get());
}

TEST_F(TheRenderer, PassesItselfToTheDrawableForPainting)
{
    EXPECT_CALL(*(drawable.get()), paint(renderer));
    renderer->render(drawable.get());
}
