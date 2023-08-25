#pragma once
#include "Movable.h"
#include "RectangularGeometry.h"

class Box : public Movable, public RectangularGeometry
{
  public:
    Box(glm::ivec2 position, RectangularGeometry size) : Movable{position}, RectangularGeometry{size}
    {
    }
};