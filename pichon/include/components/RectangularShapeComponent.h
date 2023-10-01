#pragma once
#include "../../backendsdl/include/RectangularShapePrimitiveSDL.h"
#include "Component.h"
#include "SimpleShapes.h"
#include "components/DrawableComponent.h"
#include <glm/fwd.hpp>
#include <iostream>
#include <stdexcept>

class RectangularShapeComponent : public DrawableComponent
{
  public:
    RectangularShapeComponent(GameObject *owner, DrawableComponentManagerBase *manager_)
        : DrawableComponent(owner, manager_), m_manager{nullptr}, m_ballShape{glm::ivec2{100, 100},
                                                                              RectangularGeometry{20, 20}}
    {
        m_manager = manager_;
        if (m_manager == nullptr)
        {
            throw std::runtime_error{"The DrawableComponentManagerBase cannot be null!"};
        }
    }

    void update(uint32_t deltatime) override
    {
        m_ballShape.draw();
        m_manager->draw(&m_ballShape);
    }

    void setColor(glm::u8vec4 color)
    {
        m_ballShape.setBackgroundColor(color);
    }

  private:
    DrawableComponentManagerBase *m_manager;
    RectangularShape m_ballShape;
};

