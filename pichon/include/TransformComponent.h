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
        return RectangularGeometry{0, 0};
    }

    void setPosition(glm::ivec2 newPosition)
    {
        m_position = newPosition;
    }

  private:
    glm::ivec2 m_position{};
};
