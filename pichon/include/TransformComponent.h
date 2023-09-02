#pragma once
#include "RectangularGeometry.h"
#include <glm/glm.hpp>

class TransformComponent
{
  public:
    [[nodiscard]] glm::ivec2 position() const
    {
        return m_position;
    }

    [[nodiscard]] RectangularGeometry size() const
    {
        return m_size;
    }

    void setPosition(glm::ivec2 newPosition)
    {
        m_position = newPosition;
    }

    void setSize(RectangularGeometry newSize)
    {
        m_size = newSize;
    }

  private:
    glm::ivec2 m_position{};
    RectangularGeometry m_size{};
};
