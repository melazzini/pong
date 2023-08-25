#pragma once
#include <glm/glm.hpp>

class Movable
{
  public:
    explicit Movable(glm::ivec2 position) : m_position{position}, m_velocity{}
    {
    }

    virtual ~Movable()
    {
    }

    [[nodiscard]] glm::ivec2 position() const
    {
        return m_position;
    }

    [[nodiscard]] glm::ivec2 velocity() const
    {
        return m_velocity;
    }

    void setVelocity(glm::ivec2 newVelocity)
    {
        m_velocity = newVelocity;
    }

    void setPosition(glm::ivec2 newPosition)
    {
        m_position = newPosition;
    }

  private:
    glm::ivec2 m_position;
    glm::ivec2 m_velocity;
};
