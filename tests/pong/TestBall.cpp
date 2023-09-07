#include "../pichon/MockRenderer.h"
#include "Ball.h"
#include "Game.h"
#include "RectangularGeometry.h"
#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using testing::Eq;
using testing::Ne;

TEST(TheBall, HasTransformComponent)
{
    MockRenderer renderer;
    Ball ball{&renderer};
    ASSERT_TRUE(ball.hasComponent<TransformComponent>());
}
TEST(TheBall, HasRectangularShapeComponent)
{
    MockRenderer renderer;
    Ball ball{&renderer};
    ASSERT_TRUE(ball.hasComponent<RectangularShapeComponent>());
}

TEST(TheBall, HasBoxColliderComponent)
{
    MockRenderer renderer;
    Ball ball{&renderer};
    ASSERT_TRUE(ball.hasComponent<BoxColliderComponent>());
}

TEST(TheBall, StartsAtTheCenterOfTheScreen)
{
    MockRenderer renderer;
    Ball ball{&renderer};
    ASSERT_THAT(ball.component<TransformComponent>()->position().x, Eq(WINDOW_SIZE.width() / 2));
    ASSERT_THAT(ball.component<TransformComponent>()->position().y, Eq(WINDOW_SIZE.height() / 2));
}

struct ABall : testing::Test
{
    MockRenderer renderer;
    Ball ball{&renderer};
    glm::ivec2 dummyPosition{10, 100};
};

TEST_F(ABall, CanChangeItsYPosition)
{
    ASSERT_THAT(ball.component<TransformComponent>()->position(), Ne(dummyPosition));
    ball.component<TransformComponent>()->setPosition(dummyPosition);
    ASSERT_THAT(ball.component<TransformComponent>()->position(), Eq(dummyPosition));
}

