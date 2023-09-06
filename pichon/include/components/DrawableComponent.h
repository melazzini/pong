#pragma once
#include "TransformComponent.h"
#include "components/Component.h"

struct IDrawableComponentManager : public ComponentManager
{
};
class DrawableComponentManager : public IDrawableComponentManager
{
  public:
    static DrawableComponentManager *getInstance();

  private:
    DrawableComponentManager() = default;
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
