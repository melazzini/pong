#include "RectangularShapePrimitiveSDL.h"
#include "RendererPrimitiveSDL.h"

void RectangularShapePrimitiveSDL::paintWithRendererPrimitive(IRendererPrimitive *rendererPrimitive)
{
    auto rendererPimpl{static_cast<RendererPrimitiveSDL *>(rendererPrimitive)};
    const auto &pos{position()};
    const auto &size_{size()};
    SDL_Rect rect{m_position.x, m_position.y, m_size.x, m_size.y};
    SDL_SetRenderDrawColor(rendererPimpl->m_renderer.get(), m_backgroundColor.r, m_backgroundColor.g,
                           m_backgroundColor.b, m_backgroundColor.a);
    SDL_RenderFillRect(rendererPimpl->m_renderer.get(), &rect);
}

void RectangularShapePrimitiveSDL::setBackgroundColor(glm::u8vec4 newcolor)
{
    m_backgroundColor = newcolor;
}

glm::u8vec4 RectangularShapePrimitiveSDL::backgroundColor() const
{
    return m_backgroundColor;
}

void RectangularShapePrimitiveSDL::setPosition(glm::ivec2 newPosition)
{
    m_position = newPosition;
}

void RectangularShapePrimitiveSDL::setSize(glm::ivec2 newSize)
{
    m_size = newSize;
}

glm::ivec2 RectangularShapePrimitiveSDL::size() const
{
    return m_size;
}

glm::ivec2 RectangularShapePrimitiveSDL::position() const
{
    return m_position;
}
