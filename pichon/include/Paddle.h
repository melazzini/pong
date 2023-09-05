#pragma once
#include "Component.h"
#include "GameObject.h"

struct RectangularShapeComponent : Component
{
    void update(float deltatime) override
    {
    }
};

struct InputComponent : Component
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
