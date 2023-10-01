#include "BackendContextSDL.h"
#include "RendererPrimitiveSDL.h"

BackendContextSDL *BackendContextSDL::getInstance()
{
    static BackendContextSDL backend{};
    return &backend;
}

BackendContextSDL::BackendContextSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << SDL_GetError() << std::endl;
        abort();
    }
}

std::unique_ptr<IRendererPrimitive> BackendContextSDL::rendererPrimitive()
{
    auto rendererPrimitive{std::make_unique<RendererPrimitiveSDL>(wnd)};
    renderer = rendererPrimitive->m_renderer.get();
    return rendererPrimitive;
}
std::unique_ptr<IWindowPrimitive> BackendContextSDL::windowPrimitive()
{
    auto wndPrimitive{std::make_unique<WindowPrimitive>()};
    wnd = wndPrimitive->m_window.get();
    return wndPrimitive;
}

