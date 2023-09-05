#pragma once
#include "Component.h"

class InputComponentManager : public ComponentManager
{
};

class InputComponent : public Component
{
  public:
    InputComponent(GameObject *owner, ComponentManager *manager) : Component(owner, manager)
    {
    }
    void update(float deltatime) override
    {
    }
};
