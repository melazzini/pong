//
// Created by francisco on 8/21/23.
//
#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Eq;

class Paddle
{
  public:
    explicit Paddle(glm::vec2 position) : m_position{position},m_velocity{}
    {
    }

    [[nodiscard]]glm::vec2 position() const
    {
        return m_position;
    }

    [[nodiscard]] glm::vec2 velocity()const
    {
        return m_velocity;
    }

    void setVelocity(glm::vec2 newVelocity)
    {
        m_velocity = newVelocity;
    }

    void setPosition(glm::vec2 newPosition)
    {
        m_position = newPosition;
    }

  private:
    glm::vec2 m_position;
    glm::vec2 m_velocity;
};

struct ThePaddle:testing::Test
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

TEST_F(ThePaddle,CanSetItsVelocity)
{
    Paddle paddle{initialPosition};
    paddle.setVelocity(glm::vec2{10,10});
    ASSERT_THAT(paddle.velocity(),Eq(glm::vec2{10,10}));
}

TEST_F(ThePaddle,CanSetItsPosition)
{
    Paddle paddle{initialPosition};
    paddle.setPosition(glm::vec2{10,10});
    ASSERT_THAT(paddle.position(),Eq(glm::vec2{10,10}));
}