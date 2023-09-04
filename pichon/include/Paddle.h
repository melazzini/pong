#pragma once
#include "Component.h"
#include "GameObject.h"

struct SimpleRectShapeComponent : Component
{
    void update(float deltatime) override
    {
    }
};

class Paddle : public GameObject
{
  public:
    explicit Paddle();
};
