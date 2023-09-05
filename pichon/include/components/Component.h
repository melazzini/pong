#pragma once

#include <stdexcept>
struct ComponentManager
{
    virtual ~ComponentManager() = default;
};

struct GameObject;

class Component
{
  public:
    Component(GameObject *owner, ComponentManager *manager)
    {
        if (owner == nullptr)
        {
            throw std::runtime_error{"Attemp to give a null GameObject-owner!"};
        }
        if (manager == nullptr)
        {
            throw std::runtime_error{"Attemp to give a null ComponentManager object!"};
        }
    }
    virtual void update(float deltaTime)
    {
    }

    virtual ~Component() = default;
};
