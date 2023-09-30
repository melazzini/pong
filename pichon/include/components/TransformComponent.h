#pragma once
#include "Component.h"
#include "RectangularGeometry.h"
#include <functional>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

class TransformComponentManager : public IComponentManager
{
  public:
    static TransformComponentManager *getInstance();

    bool registerComponent(IComponent *component) override;
    bool hasComponent(IComponent *component) const override;
    void updateComponents(uint32_t deltatime) override;
    void destroyComponents() override;

  private:
    TransformComponentManager() = default;
    std::vector<IComponent *> m_components;
};

class TransformComponent : public Component
{
  public:
    TransformComponent(GameObject *owner, IComponentManager *manager, glm::ivec2 initialPosition = {},
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

    void update(uint32_t deltaTime) override
    {
    }

  protected:
    glm::ivec2 m_position;
    RectangularGeometry m_size;
};

