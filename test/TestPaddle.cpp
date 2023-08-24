//
// Created by francisco on 8/21/23.
//
#include "Paddle.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Eq;
using testing::Ne;

static const glm::vec2 paddleInitialPosition{};

struct AnExistingPaddle : testing::Test
{
    Paddle paddle{paddleInitialPosition};
    glm::vec2 dummyPosition{10,-20};
    glm::vec2 dummyVelocity{10,-20};
};

TEST(APaddle, StartsAtTheGivenInitialPosition)
{
    Paddle paddle{paddleInitialPosition};
    ASSERT_THAT(paddle.position(), Eq(paddleInitialPosition));
}

TEST(APaddle, StartsAtRest)
{
    Paddle paddle{paddleInitialPosition};
    ASSERT_THAT(paddle.velocity(), Eq(glm::vec2{}));
}

TEST_F(AnExistingPaddle, CanChangeItsPosition)
{
    ASSERT_THAT(paddle.position(),Ne(dummyPosition));
    paddle.setPosition(dummyPosition);
    ASSERT_THAT(paddle.position(), Eq(dummyPosition));
}

TEST_F(AnExistingPaddle, CanChangeItsVelocity)
{
    ASSERT_THAT(paddle.velocity(),Ne(dummyVelocity));
    paddle.setVelocity(dummyVelocity);
    ASSERT_THAT(paddle.velocity(), Eq(dummyVelocity));
}