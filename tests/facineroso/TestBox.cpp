#include "Box.h"
#include "Drawable.h"
#include "Movable.h"

#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iterator>
#include <memory>

using testing::Eq;
using testing::Mock;
using testing::Ne;

static const int dummyWidth{10};
static const int dummyHeight{10};

struct MockDrawablePrimitive : IDrawablePrimitive
{
    MOCK_METHOD(void, paintWithRendererPrimitive, (IRendererPrimitive *), (override));
};

struct ABoxInstance : testing::Test
{
    std::unique_ptr<MockDrawablePrimitive> drawablePrimitive{std::make_unique<MockDrawablePrimitive>()};
};

TEST_F(ABoxInstance, IsInstantiatedWithPositionAndSizeAndIDrawablePrimitive)
{
    Box b{glm::ivec2{}, RectangularGeometry{dummyWidth, dummyHeight}, std::move(drawablePrimitive)};
}

struct ABox : ABoxInstance
{
    struct DummyRendererePrimitive : IRendererPrimitive
    {
    };
    struct DummyRenderer : IRenderer
    {
        void render(Drawable *) override
        {
        }
        IRendererPrimitive *primitive() override
        {
            return nullptr;
        }
    };
    MockDrawablePrimitive &drawablePrimitiveSpy{*drawablePrimitive.get()};
    Box box{glm::ivec2{}, RectangularGeometry{dummyWidth, dummyHeight}, std::move(drawablePrimitive)};
    std::unique_ptr<ABox::DummyRenderer> dummyRenderer{std::make_unique<ABox::DummyRenderer>()};
};

TEST_F(ABox, IsAlsoMovable)
{
    Movable *m{&box};
}

TEST_F(ABox, IsAlsoRectangularGeometry)
{
    RectangularGeometry *rectangularGeometry{&box};
}

TEST_F(ABox, IsAlsoDrawable)
{
    Drawable *drawable{&box};
    drawable->draw();
}

TEST_F(ABox, UsesItsDrawablePrimitiveAndRendererPrimitiveForPainting)
{
    EXPECT_CALL(drawablePrimitiveSpy, paintWithRendererPrimitive(dummyRenderer->primitive()));
    box.paint(dummyRenderer.get());
    Mock::VerifyAndClearExpectations(&drawablePrimitiveSpy);
    Mock::AllowLeak(&drawablePrimitiveSpy);
}
