#include "SimpleShapes.h"
#include "DrawablePrimitivesFactory.h"
#include <stdexcept>

RectangularShape::RectangularShape(glm::ivec2 position, RectangularGeometry size)
    : AbstractPrimitiveShape(position, DrawablePrimitivesFactory::rectangularDrawablePrimitive()),
      RectangularGeometry{size}, m_drawablePrimitive(nullptr)
{
    m_drawablePrimitive = dynamic_cast<IRectangularDrawablePrimitive *>(m_primitive.get());
    if (m_drawablePrimitive == nullptr)
    {
        throw std::runtime_error{"The IRectangularDrawablePrimitive cannot be null."};
    }
}

void RectangularShape::draw()
{
    m_drawablePrimitive->setPosition(position());
    m_drawablePrimitive->setSize({width(), height()});
    m_drawablePrimitive->setBackgroundColor(backgroundColor());
}
