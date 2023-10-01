#include "../include/Renderer.h"
#include "../include/Drawable.h"
#include "IPrimitives.h"
#include <memory>

Renderer::Renderer(IBackendContext *engine) : m_primitive{engine->rendererPrimitive()}
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
    return m_primitive.get();
}
