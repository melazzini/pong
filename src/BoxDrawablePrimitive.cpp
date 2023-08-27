#include "../include/BoxDrawablePrimitive.h"
#include "../include/RendererPrimitive.h"

void BoxDrawablePrimitive::paintWithRendererPrimitive(IRendererPrimitive *primitive)
{
    auto rendererPimpl{static_cast<RendererPrimitive *>(primitive)};

    SDL_Rect rect{position.x, position.y, size.x, size.y};
    SDL_SetRenderDrawColor(rendererPimpl->m_renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(rendererPimpl->m_renderer.get(), &rect);
}
