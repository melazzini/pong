#include "../include/Window.h"

Window *Window::getInstance(IBackendContext *engine)
{
    static Window w;
    return &w;
}
