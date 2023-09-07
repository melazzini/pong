#include "RectangularShape.h"
#include "../../backendsdl/include/BoxDrawablePrimitiveSDL.h"
#include <glm/fwd.hpp>
#include <iostream>

struct RectangularShape::Impl
{
    BoxDrawablePrimitiveSDL *boxDrawablePrimitive;
    glm::u8vec4 color;
};

RectangularShape::RectangularShape(glm::ivec2 position, RectangularGeometry size, glm::u8vec4 color)
    : Box(position, size, std::make_unique<BoxDrawablePrimitiveSDL>()), m_pimpl{std::unique_ptr<Impl, void (*)(Impl *)>(
                                                                            new RectangularShape::Impl, [](Impl *impl) {
                                                                                if (impl)
                                                                                {
                                                                                    delete impl;
                                                                                }
                                                                            })}
{
    m_pimpl->boxDrawablePrimitive = dynamic_cast<BoxDrawablePrimitiveSDL *>(m_primitive.get());
    m_pimpl->color = color;
}
void RectangularShape::draw()
{
    m_pimpl->boxDrawablePrimitive->position = position();
    m_pimpl->boxDrawablePrimitive->size = {width(), height()};
    m_pimpl->boxDrawablePrimitive->color = m_pimpl->color;
}

void RectangularShape::setColor(glm::u8vec4 color)
{
    m_pimpl->color = color;
}
