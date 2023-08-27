#include "../include/RendererPrimitive.h"
#include "../include/RendererSDL.h"
#include <memory>

RendererSDL::RendererSDL(BackendContext *engine) : m_pimpl{std::make_unique<RendererPrimitive>(engine->wnd)}
{
    engine->renderer = m_pimpl->m_renderer.get();
}

RendererSDL *RendererSDL::getInstance(BackendContext *engine)
{
    static RendererSDL renderer(engine);
    return &renderer;
}

void RendererSDL::render(Drawable *drawable)
{
    drawable->draw();
    drawable->paint(this);
}

IRendererPrimitive *RendererSDL::primitive()
{
    return m_pimpl.get();
}
