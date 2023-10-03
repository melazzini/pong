#include "BackendContextSDL.h"
#include "RendererPrimitiveSDL.h"
#include "WindowPrimitiveSDL.h"
#include <stdexcept>

SDL_Window *BackendContextSDL::wnd{};
SDL_Renderer *BackendContextSDL::renderer{};

BackendContextSDL *BackendContextSDL::getInstance()
{
    static BackendContextSDL backend{};
    return &backend;
}

BackendContextSDL::BackendContextSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        throw std::runtime_error{SDL_GetError()};
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

