#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Interfaces.h"
class Ball : public GameObject
{
  public:
    Ball(IRenderer *renderer);
};
