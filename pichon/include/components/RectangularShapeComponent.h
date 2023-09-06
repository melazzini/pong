#pragma once
#include "Component.h"
#include "components/DrawableComponent.h"
#include <iostream>

class RectangularShapeComponent : public DrawableComponent
{
  public:
    RectangularShapeComponent(GameObject *owner, ComponentManager *manager) : DrawableComponent(owner, manager)
    {
    }

    void update(float deltatime) override
    {
        std::cout << "RectangularShapeComponent: " << __FUNCTION__ << std::endl;
        std::cout << __FUNCTION__ << std::endl;
    }
};

