#pragma once
#include "TransformComponent.h"
#include "components/Component.h"
#include <iostream>

class DrawableComponent : public Component
{
  public:
    DrawableComponent(GameObject *owner, ComponentManager *manager) : Component(owner, manager)
    {
    }

    void update(float deltaTime) override
    {
        std::cout << "DrawableComponent: " << __FUNCTION__ << std::endl;
    }
};

class IDrawableComponentManager : public ComponentManager
{
  public:
    void update(float deltaTime) override
    {
        for (auto component : m_components)
        {
            component->update(deltaTime);
        }
    }

    void registerComponent(Component *component) override
    {
        std::cout << "IDrawableComponentManager: " << __FUNCTION__ << std::endl;
        if (dynamic_cast<DrawableComponent *>(component))
        {
            m_components.push_back(component);
        }
    }

  private:
    std::vector<Component *> m_components;
};
class DrawableComponentManager : public IDrawableComponentManager
{
  public:
    static DrawableComponentManager *getInstance();

  private:
    DrawableComponentManager() = default;
};

