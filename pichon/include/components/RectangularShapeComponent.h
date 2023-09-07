#pragma once
#include "../../backendsdl/include/BoxDrawablePrimitiveSDL.h"
#include "Box.h"
#include "Component.h"
#include "components/DrawableComponent.h"
#include <glm/fwd.hpp>
#include <iostream>

struct BallShape : Box
{
    BallShape(glm::ivec2 position, int size)
        : Box(position, RectangularGeometry{size, size}, std::make_unique<BoxDrawablePrimitiveSDL>()),
          m_boxDrawablePrimitive(dynamic_cast<BoxDrawablePrimitiveSDL *>(m_primitive.get()))
    {
    }

    void draw() override
    {
        m_boxDrawablePrimitive->position = position();
        m_boxDrawablePrimitive->size = {width(), height()};
        m_boxDrawablePrimitive->color = m_color;
    }

    void setColor(glm::u8vec4 color)
    {
        m_color = color;
    }

  private:
    BoxDrawablePrimitiveSDL *m_boxDrawablePrimitive;
    glm::u8vec4 m_color{255, 0, 0, 255};
};
class RectangularShapeComponent : public DrawableComponent
{
  public:
    RectangularShapeComponent(GameObject *owner, ComponentManager *manager_)
        : DrawableComponent(owner, manager_), m_manager{nullptr}, m_ballShape{glm::ivec2{100, 100}, 20}
    {
        m_manager = dynamic_cast<DrawableComponentManagerBase *>(manager_);
        if (m_manager != nullptr)
        {
            std::cout << "SUPER!!!" << std::endl;
        }
    }

    void update(float deltatime) override
    {
        m_ballShape.draw();
        m_manager->draw(&m_ballShape);
    }

    void setColor(glm::u8vec4 color)
    {
        m_ballShape.setColor(color);
    }

  private:
    DrawableComponentManagerBase *m_manager;
    BallShape m_ballShape;
};

