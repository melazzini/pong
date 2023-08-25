#include <glm/ext/vector_float2.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Eq;
using testing::Ne;

class Ball
{
  public:
    Ball(glm::vec2 position)
    {
    }

    glm::vec2 position() const
    {
        return {0, 0};
    }
};

TEST(ABall, StartsAtTheGivenInitialPosition)
{
    Ball ball{glm::vec2{}};
    ASSERT_THAT(ball.position(), Eq(glm::vec2{}));
}
