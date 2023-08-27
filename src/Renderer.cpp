#include "../include/Renderer.h"
#include "../include/RendererPrimitive.h"
#include <memory>

Renderer::Renderer(BackendContext *engine) : m_pimpl{std::make_unique<RendererPrimitive>(engine->wnd)}
{
    engine->renderer = m_pimpl->m_renderer.get();
}

Renderer *Renderer::getInstance(BackendContext *engine)
{
    static Renderer renderer(engine);
    return &renderer;
}

void Renderer::render(Drawable *drawable)
{
    drawable->draw();
    drawable->paint(this);
}

IRendererPrimitive *Renderer::primitive()
{
    return m_pimpl.get();
}
