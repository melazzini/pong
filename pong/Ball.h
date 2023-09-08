#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Interfaces.h"
#include "RectangularShape.h"
#include "components/DrawableComponent.h"
class Ball : public GameObject
{
  public:
    Ball(IRenderer *renderer);
};

class BallDrawableComponent : public DrawableComponent
{
  public:
    BallDrawableComponent(GameObject *owner, DrawableComponentManagerBase *manager_)
        : DrawableComponent(owner, manager_), m_shape{glm::ivec2{10, 100}, RectangularGeometry{50, 50},
                                                      glm::u8vec4{255, 0, 0, 255}}
    {
        m_drawable = &m_shape;
    }

  private:
    RectangularShape m_shape;
};
