#include "../pichon/MockEventManager.h"
#include "../pichon/MockRenderer.h"
#include "Game.h"
#include "Paddle.h"
#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using testing::Eq;
using testing::Ne;

struct ThePaddle : testing::Test
{
    MockEventManager eventManger;
    MockRenderer renderer;
};

TEST_F(ThePaddle, HasConstrainedTransformComponent)
{
    Paddle paddle{&eventManger, &renderer};
    ASSERT_TRUE(paddle.hasComponent<ConstrainedTransformComponent>());
}

TEST_F(ThePaddle, HasRectangularShapeComponent)
{
    Paddle paddle{&eventManger, &renderer};
    ASSERT_TRUE(paddle.hasComponent<RectangularShapeComponent>());
}

TEST_F(ThePaddle, HasInputComponent)
{
    Paddle paddle{&eventManger, &renderer};
    ASSERT_TRUE(paddle.hasComponent<InputComponent>());
}

TEST_F(ThePaddle, HasBoxColliderComponent)
{
    Paddle paddle{&eventManger, &renderer};
    ASSERT_TRUE(paddle.hasComponent<BoxColliderComponent>());
}

TEST_F(ThePaddle, StartsCenteredOnTheLeftOfTheScreenWithAGivenSize)
{
    Paddle paddle{&eventManger, &renderer};
    ASSERT_THAT(paddle.component<TransformComponent>()->position().x,
                Eq(paddle.component<TransformComponent>()->size().width() / 2));
    ASSERT_THAT(paddle.component<TransformComponent>()->position().y, Eq(WINDOW_SIZE.height() / 2));
}

struct APaddle : testing::Test
{
    MockEventManager eventManger;
    MockRenderer renderer;
    Paddle paddle{&eventManger, &renderer};
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
