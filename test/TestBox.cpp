#include "Box.h"
#include "Drawable.h"
#include "Movable.h"

#include <glm/glm.hpp>
#include <gmock/gmock.h>

using testing::Eq;
using testing::Ne;

static const int dummyWidth{10};
static const int dummyHeight{10};

struct MockDrawablePrimitive : DrawablePrimitive
{
    MOCK_METHOD(void, paintWithRenderer, (Renderer *), (override));
};

MockDrawablePrimitive drawablePrimitive;

struct ABox : testing::Test
{
    MockDrawablePrimitive drawablePrimitive2;
    Box box{glm::ivec2{}, RectangularGeometry{dummyWidth, dummyHeight}, &drawablePrimitive2};
    Renderer renderer;
};

TEST(ABoxInstance, IsInstantiatedWithPositionAndSizeAndDrawablePrimitive)
{
    Box b{glm::ivec2{}, RectangularGeometry{dummyWidth, dummyHeight}, &drawablePrimitive};
}

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

TEST_F(ABox, UsesItsDrawablePrimitiveAndRendererForPainting)
{
    EXPECT_CALL(drawablePrimitive2, paintWithRenderer(&renderer));
    box.paint(&renderer);
}
