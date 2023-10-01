#pragma once
#include "AbstractPrimitiveShape.h"
#include "RectangularGeometry.h"

/**
 * @brief This is a rectangular shape.
 *
 * @warning THIS CLASS DEPENDS ON THE DrawablePrimitivesFactory CLASS, WHICH
 * MUST BE PROVIDED BY THE BACKEND OR IT CAN BE A DUMMY IMPLEMENTATION.
 *
 * @warning We probably will change the name of this class.
 *
 * @note AbstractPrimitiveShape does not depend on DrawablePrimitivesFactory,
 * and you should use that class for unit tests (to derive your mocks) or if
 * you want a custom shape implementation.
 *
 * @see AbstractPrimitiveShape
 */
class RectangularShape : public AbstractPrimitiveShape, public RectangularGeometry
{
  public:
    RectangularShape(glm::ivec2 position, RectangularGeometry size);
    void draw() override;

  private:
    IRectangularDrawablePrimitive *m_drawablePrimitive;
};

class CircularShape : public AbstractPrimitiveShape
{
  public:
    CircularShape(glm::ivec2 position, int32_t radius);
    void draw() override;
};

class TriangularShape : public AbstractPrimitiveShape
{
  public:
    TriangularShape(TriangleVerticesPosition verticesPos);
    void draw() override;
};
