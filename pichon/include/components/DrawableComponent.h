#pragma once
#include "TransformComponent.h"
#include "components/Component.h"

class DrawableComponentManager : public ComponentManager
{
};

class DrawableComponent : public Component
{
  public:
    DrawableComponent(GameObject *owner, ComponentManager *manager) : Component(owner, manager)
    {
    }

    void update(float deltaTime) override
    {
    }
};
