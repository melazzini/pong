#include "Game.h"
#include "Paddle.h"
#include "TransformComponent.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using testing::Eq;
using testing::Ne;

class Ball : public GameObject
{
  public:
    Ball()
    {
        auto transform = addComponent<TransformComponent>();
        transform->setPosition(glm::ivec2{WINDOW_SIZE.width() / 2, WINDOW_SIZE.height() / 2});
    }
};

TEST(TheBall, StartsAtTheCenterOfTheScreen)
{
    Game game{};
    Ball ball{};
    ASSERT_THAT(ball.component<TransformComponent>()->position().x, Eq(game.windowSize().width() / 2));
    ASSERT_THAT(ball.component<TransformComponent>()->position().y, Eq(game.windowSize().height() / 2));
}

struct ABall : testing::Test
{
    Ball ball{};
    glm::ivec2 dummyPosition{10, 100};
};

TEST_F(ABall, CanChangeItsYPosition)
{
    ASSERT_THAT(ball.component<TransformComponent>()->position(), Ne(dummyPosition));
    ball.component<TransformComponent>()->setPosition(dummyPosition);
    ASSERT_THAT(ball.component<TransformComponent>()->position(), Eq(dummyPosition));
}

