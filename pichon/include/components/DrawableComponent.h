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

class DrawableComponentManagerBase : public ComponentManager
{
  public:
    DrawableComponentManagerBase()
    {
    }
};

class DrawableComponentManager : public DrawableComponentManagerBase
{
  public:
    static DrawableComponentManager *getInstance();

  private:
    DrawableComponentManager() = default;
};

