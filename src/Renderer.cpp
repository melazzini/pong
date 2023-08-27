#include "../include/Renderer.h"
#include <memory>

Renderer::Renderer(IBackendContext *engine) : m_pimpl{engine->rendererPrimitive()}
{
}

Renderer *Renderer::getInstance(IBackendContext *engine)
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
