#pragma once
#include "Component.h"

class RectangularShapeComponentManager : public ComponentManager
{
};

class RectangularShapeComponent : public Component
{
  public:
    RectangularShapeComponent(GameObject *owner, ComponentManager *manager) : Component(owner, manager)
    {
    }

    void update(float deltatime) override
    {
    }
};

