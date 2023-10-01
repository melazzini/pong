#pragma once
#include "BackendContextInterface.h"
#include "EventUtils.h"
#include "IPrimitives.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <iostream>
#include <memory>
#include <stdexcept>

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

    using WindowBackendSDL = std::unique_ptr<SDL_Window, void (*)(SDL_Window *)>;
    struct WindowPrimitive : IWindowPrimitive
    {
        WindowBackendSDL m_window;

        WindowPrimitive() : m_window{makeUniqueWindow()}
        {
        }

        void clearWindow(glm::u8vec4 color) override
        {
            SDL_SetRenderDrawColor(BackendContextSDL::renderer, color.r, color.g, color.b, color.a);
            SDL_RenderClear(BackendContextSDL::renderer);
        }

        void updateWindow() override
        {
            SDL_RenderPresent(BackendContextSDL::renderer);
        }

      private:
        WindowBackendSDL makeUniqueWindow()
        {
            auto wnd{SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800,
                                      SDL_WINDOW_OPENGL)};
            if (wnd == nullptr)
            {
                throw std::runtime_error{SDL_GetError()};
            }
            return WindowBackendSDL{wnd, [](SDL_Window *_w) {
                                        if (_w)
                                        {
                                            SDL_DestroyWindow(_w);
                                        }
                                    }};
        }
    };

  private:
    BackendContextSDL();
};
/*
 *
 */
