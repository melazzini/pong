#pragma once
#include "BackendContextInterface.h"
#include "EventUtils.h"
#include "IPrimitives.h"
#include <memory>

struct SDL_Window;
struct SDL_Renderer;
struct BackendContextSDL : IBackendContext
{
    static SDL_Window *wnd;
    static SDL_Renderer *renderer;

    static BackendContextSDL *getInstance();

    std::unique_ptr<IRendererPrimitive> rendererPrimitive() override;
    std::unique_ptr<IWindowPrimitive> windowPrimitive() override;

  private:
    BackendContextSDL();
};
/*
 *
 */
