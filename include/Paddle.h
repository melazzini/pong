//
// Created by francisco on 8/24/23.
//

#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H

#include <glm/vec2.hpp>

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

#endif // PONG_PADDLE_H
