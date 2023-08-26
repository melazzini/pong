#include "Box.h"
#include "Drawable.h"
#include "Movable.h"

#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iterator>
#include <memory>

using testing::Eq;
using testing::Ne;

static const int dummyWidth{10};
static const int dummyHeight{10};

struct MockDrawablePrimitive : IDrawablePrimitive
{
    MOCK_METHOD(void, paintWithIRenderer, (IRenderer *), (override));
};

struct ABoxInstance : testing::Test
{
    MockDrawablePrimitive drawablePrimitive;
};

TEST_F(ABoxInstance, IsInstantiatedWithPositionAndSizeAndIDrawablePrimitive)
{
    Box b{glm::ivec2{}, RectangularGeometry{dummyWidth, dummyHeight}, &drawablePrimitive};
}

struct ABox : ABoxInstance
{
    struct DummyRenderer : IRenderer
    {
    };
    Box box{glm::ivec2{}, RectangularGeometry{dummyWidth, dummyHeight}, &drawablePrimitive};
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
TEST_F(ABox, UsesItsIDrawablePrimitiveAndIRendererForPainting)
{
    EXPECT_CALL(drawablePrimitive, paintWithIRenderer(dummyRenderer.get()));
    box.paint(dummyRenderer.get());
}
