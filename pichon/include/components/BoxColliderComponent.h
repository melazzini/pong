#pragma once
#include "Component.h"

class BoxColliderComponentManager : public ComponentManager
{
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

