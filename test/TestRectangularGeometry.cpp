#include "RectangularGeometry.h"
#include <gmock/gmock.h>

using testing::Eq;
using testing::Ne;

TEST(ARectangularGeometry, StartsWithGivenWidthAndHeight)
{
    RectangularGeometry rectGeometry{10, 10};
    ASSERT_THAT(rectGeometry.width(), Eq(10));
    ASSERT_THAT(rectGeometry.height(), Eq(10));
}
struct AnExistingRectangularGeometry : testing::Test
{
    RectangularGeometry rectGeometry{0, -1};
};

TEST_F(AnExistingRectangularGeometry, CanBeFullyResized)
{
    ASSERT_THAT(rectGeometry.width(), Ne(10));
    ASSERT_THAT(rectGeometry.height(), Ne(11));

    rectGeometry.resize(10, 11);

    ASSERT_THAT(rectGeometry.width(), Eq(10));
    ASSERT_THAT(rectGeometry.height(), Eq(11));
}
