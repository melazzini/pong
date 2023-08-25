//
// Created by francisco on 8/21/23.
//
#include "Movable.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Eq;
using testing::Ne;

static const glm::ivec2 movableInitialPosition{};

struct AnExistingMovable : testing::Test
{
    Movable movable{movableInitialPosition};
    glm::ivec2 dummyPosition{10, -20};
    glm::ivec2 dummyVelocity{10, -20};
};

TEST(AMovable, StartsAtTheGivenInitialPosition)
{
    Movable movable{movableInitialPosition};
    ASSERT_THAT(movable.position(), Eq(movableInitialPosition));
}

TEST(AMovable, StartsAtRest)
{
    Movable movable{movableInitialPosition};
    ASSERT_THAT(movable.velocity(), Eq(glm::ivec2{}));
}

TEST_F(AnExistingMovable, CanChangeItsPosition)
{
    ASSERT_THAT(movable.position(), Ne(dummyPosition));
    movable.setPosition(dummyPosition);
    ASSERT_THAT(movable.position(), Eq(dummyPosition));
}

TEST_F(AnExistingMovable, CanChangeItsVelocity)
{
    ASSERT_THAT(movable.velocity(), Ne(dummyVelocity));
    movable.setVelocity(dummyVelocity);
    ASSERT_THAT(movable.velocity(), Eq(dummyVelocity));
}
