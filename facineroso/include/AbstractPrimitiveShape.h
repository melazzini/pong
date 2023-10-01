#pragma once
#include "Drawable.h"
#include "Movable.h"

/**
 * @brief An AbstractPrimitiveShape is a movable and drawable 2d shape with a background color.
 *
 * @note The definition of the position of the sape depends on the concrete implementation.
 */
class AbstractPrimitiveShape : public Movable, public Drawable
{
  public:
    AbstractPrimitiveShape(glm::ivec2 position, std::unique_ptr<IDrawablePrimitive> drawablePrimitive)
        : Movable{position}, Drawable{std::move(drawablePrimitive)}
    {
    }

    void setBackgroundColor(glm::u8vec4 newColor)
    {
        m_color = newColor;
    }

    glm::u8vec4 backgroundColor() const
    {
        return m_color;
    }

  private:
    glm::u8vec4 m_color;
};
