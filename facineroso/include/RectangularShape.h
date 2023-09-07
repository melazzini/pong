#pragma once
#include "Box.h"
#include "RectangularGeometry.h"

class RectangularShape : public Box
{
  public:
    RectangularShape(glm::ivec2 position, RectangularGeometry size, glm::u8vec4 color);

    void draw() override;

    void setColor(glm::u8vec4 color);

    RectangularShape();
    ~RectangularShape() = default;

  private:
    struct Impl;
    std::unique_ptr<Impl, void (*)(Impl *)> m_pimpl;
};
