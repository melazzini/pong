#include "DrawableComponent.h"
#include "Game.h"
#include "Paddle.h"
#include "TransformComponent.h"
#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using testing::Eq;
using testing::Ne;

TEST(ThePaddle, HasConstrainedTransformComponent)
{
    Paddle paddle{};
    ASSERT_TRUE(paddle.hasComponent<ConstrainedTransformComponent>());
}

TEST(ThePaddle, HasSimpleRectangularShapeComponent)
{
    Paddle paddle{};
    ASSERT_TRUE(paddle.hasComponent<RectangularShapeComponent>());
}

TEST(ThePaddle, StartsCenteredOnTheLeftOfTheScreenWithAGivenSize)
{
    Game game{};
    Paddle paddle{};
    ASSERT_THAT(paddle.component<TransformComponent>()->position().x,
                Eq(paddle.component<TransformComponent>()->size().width() / 2));
    ASSERT_THAT(paddle.component<TransformComponent>()->position().y, Eq(game.windowSize().height() / 2));
}

struct APaddle : testing::Test
{
    Paddle paddle{};
    glm::ivec2 dummyPosition{40, 100};
};

TEST_F(APaddle, CanChangeItsYPosition)
{
    ASSERT_TRUE(paddle.component<TransformComponent>()->position().y != dummyPosition.y);
    paddle.component<TransformComponent>()->setPosition(dummyPosition);
    ASSERT_TRUE(paddle.component<TransformComponent>()->position().y == dummyPosition.y);
}

TEST_F(APaddle, DoesntChangeItsXCoordinateIfYouAttempToDoSo)
{
    ASSERT_TRUE(paddle.component<TransformComponent>()->position().x != dummyPosition.x);
    paddle.component<TransformComponent>()->setPosition(dummyPosition);
    ASSERT_TRUE(paddle.component<TransformComponent>()->position().x != dummyPosition.x);
}
