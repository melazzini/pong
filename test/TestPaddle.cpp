//
// Created by francisco on 8/21/23.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glm/glm.hpp>

using testing::Eq;

struct Paddle
{
    glm::vec2 position{};
};

TEST(ThePaddle, StartsAtTopLeftPossition)
{
    Paddle paddle;
    ASSERT_THAT(paddle.position,Eq(glm::vec2{}));
}