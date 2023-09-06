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
    IDrawableComponentManager()
        : ComponentManager([](Component *component) { return dynamic_cast<DrawableComponent *>(component) != nullptr; })
    {
    }
    void update(float deltaTime) override
    {
        for (auto component : m_components)
        {
            component->update(deltaTime);
        }
    }
};
class DrawableComponentManager : public IDrawableComponentManager
{
  public:
    static DrawableComponentManager *getInstance();

  private:
    DrawableComponentManager() = default;
};

