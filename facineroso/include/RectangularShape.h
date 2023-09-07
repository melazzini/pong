#pragma once
#include "Box.h"

class RectangularShape : public Box
{
  public:
    RectangularShape(glm::ivec2 position, int size, glm::u8vec4 color);

    void draw() override;

    void setColor(glm::u8vec4 color);

    RectangularShape();
    ~RectangularShape() = default;

  private:
    struct Impl;
    std::unique_ptr<Impl, void (*)(Impl *)> m_pimpl;
};
