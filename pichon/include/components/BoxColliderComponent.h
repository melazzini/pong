#pragma once
#include "Component.h"

class BoxColliderComponentManager : public ComponentManager
{
  public:
    static BoxColliderComponentManager *getInstance();

  private:
    BoxColliderComponentManager() = default;
};

struct BoxColliderComponent : Component
{
    BoxColliderComponent(GameObject *owner, ComponentManager *manager) : Component(owner, manager)
    {
    }
    void update(float deltatime) override
    {
    }
};

