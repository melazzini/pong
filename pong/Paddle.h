#pragma once
#include "GameObject.h"
#include "Interfaces.h"

class Paddle : public GameObject
{
  public:
    explicit Paddle(IEventManager *, IRenderer *renderer);
};
