#pragma once
#include "Drawable.h"
#include "Movable.h"
#include "RectangularGeometry.h"

class Box : public Movable, public RectangularGeometry, public Drawable
{
  public:
    Box(glm::ivec2 position, RectangularGeometry size) : Movable{position}, RectangularGeometry{size}, Drawable{}
    {
    }
};