#include "../include/Window.h"

Window::Window(IBackendContext *engine) : m_primitive{engine->windowPrimitive()}
{
}

Window *Window::getInstance(IBackendContext *engine)
{
    static Window w(engine);
    return &w;
}

void Window::clear(glm::u8vec4 color)
{
    m_primitive->clearWindow(color);
}

void Window::present()
{
    m_primitive->updateWindow();
}
