#include "../include/RendererSDL.h"

void BoxDrawablePrimitive::paintWithIRenderer(IRenderer *renderer)
{
    auto rendererSDL{dynamic_cast<RendererSDL *>(renderer)};
    if (rendererSDL == nullptr)
    {
        throw std::runtime_error{"Bad SDL_Renderer"};
    }
    SDL_Rect rect{position.x, position.y, size.x, size.y};
    SDL_SetRenderDrawColor(rendererSDL->m_renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(rendererSDL->m_renderer.get(), &rect);
}
