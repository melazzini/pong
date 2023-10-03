#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>

#include <iostream>
#include <memory>
#include <stdexcept>

#include "BackendContextInterface.h"
#include "EventUtils.h"
#include "IPrimitives.h"

struct EventManagerPrimitiveSDL : IEventManagerPrimitive
{
    void pollEvents(IEventManager &eventManager) const override;
    bool isKeyPressed(Keyboard key) const override;
};

struct EventManagerPrimitiveProviderSDL : backendContext::IEventManagerPrimitiveProvider
{
    std::unique_ptr<IEventManagerPrimitive> provide() const override
    {
        return std::make_unique<EventManagerPrimitiveSDL>();
    }
};

struct BackendContextSDL : IBackendContext
{
    inline static SDL_Window *wnd{};
    inline static SDL_Renderer *renderer{};

    static BackendContextSDL *getInstance();

    std::unique_ptr<IRendererPrimitive> rendererPrimitive() override;
    std::unique_ptr<IWindowPrimitive> windowPrimitive() override;

  private:
    BackendContextSDL();
};
/*
 *
 */
