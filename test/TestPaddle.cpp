//
// Created by francisco on 8/21/23.
//
#include "Paddle.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Eq;

struct ThePaddle : testing::Test
{
    glm::vec2 initialPosition{};
};

TEST_F(ThePaddle, StartsAtTheInitialPosition)
{
    Paddle paddle{initialPosition};
    ASSERT_THAT(paddle.position(), Eq(initialPosition));
}

TEST_F(ThePaddle, StartsAtRest)
{
    Paddle paddle{initialPosition};
    ASSERT_THAT(paddle.velocity(), Eq(glm::vec2{}));
}

TEST_F(ThePaddle, CanSetItsVelocity)
{
    Paddle paddle{initialPosition};
    paddle.setVelocity(glm::vec2{10, 10});
    ASSERT_THAT(paddle.velocity(), Eq(glm::vec2{10, 10}));
}

TEST_F(ThePaddle, CanSetItsPosition)
{
    Paddle paddle{initialPosition};
    paddle.setPosition(glm::vec2{10, 10});
    ASSERT_THAT(paddle.position(), Eq(glm::vec2{10, 10}));
}