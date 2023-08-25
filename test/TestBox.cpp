#include "Box.h"

#include <glm/glm.hpp>
#include <gmock/gmock.h>

using testing::Eq;
using testing::Ne;

static const int dummyWidth{10};
static const int dummyHeight{10};

TEST(ABox, IsInstantiatedWithPositionAndSize)
{
    Box b{glm::ivec2{}, RectangularGeometry{dummyWidth, dummyHeight}};
}

TEST(ABox, IsAlsoMovable)
{
    std::unique_ptr<Movable> movable{std::make_unique<Box>(glm::ivec2{}, RectangularGeometry{dummyWidth, dummyHeight})};
}

TEST(ABox, IsAlsoRectangularGeometry)
{
    std::unique_ptr<RectangularGeometry> rectGeometry{
        std::make_unique<Box>(glm::ivec2{}, RectangularGeometry{dummyWidth, dummyHeight})};
    rectGeometry.reset(nullptr);
}

TEST(ABox, IsAlsoDrawable)
{
    std::unique_ptr<Drawable> rectGeometry{
        std::make_unique<Box>(glm::ivec2{}, RectangularGeometry{dummyWidth, dummyHeight})};
    rectGeometry.reset(nullptr);
}