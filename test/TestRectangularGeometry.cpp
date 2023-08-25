#include <glm/glm.hpp>
#include <gmock/gmock.h>

using testing::Eq;
using testing::Ne;

class RectangularGeometry
{
  public:
    RectangularGeometry(int w, int h)
    {
    }

    int width() const
    {
        return 10;
    }

    int height() const
    {
        return 10;
    }
};

TEST(ARectangularGeometry, StartsWithGivenWidthAndHeight)
{
    RectangularGeometry rectGeometry{10, 10};
    ASSERT_THAT(rectGeometry.width(), Eq(10));
    ASSERT_THAT(rectGeometry.height(), Eq(10));
}
