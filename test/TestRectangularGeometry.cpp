#include "RectangularGeometry.h"
#include <glm/fwd.hpp>
#include <gmock/gmock.h>

using testing::Eq;
using testing::Ne;

static const int dummyInitialWidth{10};
static const int dummyInitialHeight{10};

TEST(ARectangularGeometry, StartsWithGivenWidthAndHeight)
{
    RectangularGeometry rectGeometry{dummyInitialWidth, dummyInitialHeight};
    ASSERT_THAT(rectGeometry.width(), Eq(dummyInitialWidth));
    ASSERT_THAT(rectGeometry.height(), Eq(dummyInitialHeight));
}
struct AnExistingRectangularGeometry : testing::Test
{
    RectangularGeometry rectGeometry{dummyInitialWidth, dummyInitialHeight};
    static const int newDummyWidth{100};
    static const int newDummyHeight{-10};
};

TEST_F(AnExistingRectangularGeometry, CanBeFullyResized)
{
    ASSERT_THAT(rectGeometry.width(), Ne(newDummyWidth));
    ASSERT_THAT(rectGeometry.height(), Ne(newDummyHeight));

    rectGeometry.resize(newDummyWidth, newDummyHeight);

    ASSERT_THAT(rectGeometry.width(), Eq(newDummyWidth));
    ASSERT_THAT(rectGeometry.height(), Eq(newDummyHeight));
}

TEST_F(AnExistingRectangularGeometry, CanChangeItsWidthOnly)
{
    ASSERT_THAT(rectGeometry.width(), Ne(newDummyWidth));
    rectGeometry.setWidth(newDummyWidth);
    ASSERT_THAT(rectGeometry.width(), Eq(newDummyWidth));
}

TEST_F(AnExistingRectangularGeometry, CanChangeItsHeihtOnly)
{
    ASSERT_THAT(rectGeometry.height(), Ne(newDummyHeight));
    rectGeometry.setHeight(newDummyHeight);
    ASSERT_THAT(rectGeometry.height(), Eq(newDummyHeight));
}
