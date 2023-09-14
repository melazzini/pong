#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Interfaces.h"
#include "RectangularShape.h"
#include "components/DrawableComponent.h"
#include "components/TransformComponent.h"
#include <iostream>
class Ball : public GameObject
{
  public:
    Ball(IRenderer *renderer);
};

class BallDrawableComponent : public DrawableComponent
{
  public:
    BallDrawableComponent(GameObject *owner, DrawableComponentManagerBase *manager_)
        : DrawableComponent(owner, manager_), m_shape{glm::ivec2{250, 150}, RectangularGeometry{200, 20},
                                                      glm::u8vec4{255, 0, 0, 255}}
    {
        m_drawable = &m_shape;
        m_owner = owner;
    }

    void update(uint32_t deltatime) override
    {
        auto transform = m_owner->component<TransformComponent>();
        m_shape.setPosition(transform->position());
        m_shape.resize(transform->size().width(), transform->size().height());
    }

  private:
    RectangularShape m_shape;
    GameObject *m_owner;
};
