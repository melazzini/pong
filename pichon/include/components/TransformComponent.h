#pragma once
#include "Component.h"
#include "RectangularGeometry.h"
#include <functional>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

class TransformComponentManager : public ComponentManager
{
};

class TransformComponent : public Component
{
  public:
    TransformComponent(GameObject *owner, ComponentManager *manager, glm::ivec2 initialPosition = {},
                       RectangularGeometry initialSize = RectangularGeometry{})
        : Component(owner, manager), m_position{initialPosition}, m_size{initialSize}
    {
    }

    [[nodiscard]] glm::ivec2 position() const
    {
        return m_position;
    }

    [[nodiscard]] RectangularGeometry size() const
    {
        return m_size;
    }

    virtual void setPosition(glm::ivec2 newPosition)
    {
        m_position = newPosition;
    }

    virtual void setSize(RectangularGeometry newSize)
    {
        m_size = newSize;
    }

    void update(float deltaTime) override
    {
    }

  protected:
    glm::ivec2 m_position;
    RectangularGeometry m_size;
};

class ConstrainedTransformComponent : public TransformComponent
{
  public:
    ConstrainedTransformComponent(
        GameObject *owner, ComponentManager *manager, glm::ivec2 initialPosition, RectangularGeometry initialSize,
        std::function<glm::ivec2(std::pair<const glm::ivec2 &, const glm::ivec2 &>)> positionConstraint)
        : TransformComponent(owner, manager, initialPosition, initialSize), m_constraintNewPosition{
                                                                                std::move(positionConstraint)}
    {
    }
    void setPosition(glm::ivec2 newPosition)
    {
        m_position = m_constraintNewPosition({m_position, newPosition});
    }

  private:
    std::function<glm::ivec2(std::pair<const glm::ivec2 &, const glm::ivec2 &>)> m_constraintNewPosition;
};
