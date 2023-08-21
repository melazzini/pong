//
// Created by francisco on 8/21/23.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::Eq;

struct Paddle
{
    int x{};
    int y{};
};

TEST(ThePaddle, StartsAtTopLeftPossition)
{
    Paddle paddle;
    ASSERT_THAT(paddle.x,Eq(0));
    ASSERT_THAT(paddle.y,Eq(0));
}