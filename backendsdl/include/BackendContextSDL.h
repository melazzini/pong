#pragma once
#include "BackendContextInterface.h"
#include "EventUtils.h"
#include "Events.h"
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
    void pollEvents(IEventManager &eventManager) const override
    {

        SDL_Event evt;
        while (SDL_PollEvent(&evt))
        {
            if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE)
            {
                eventManager.enqueueEvent(std::make_unique<EventQuit>());
            }
            else if (evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                eventManager.enqueueEvent(std::make_unique<EventQuit>());
            }

            if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_RIGHT)
            {
                eventManager.enqueueEvent(std::make_unique<ArrowKeyPressed>(ArrowKey::RIGHT));
            }
            if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_LEFT)
            {
                eventManager.enqueueEvent(std::make_unique<ArrowKeyPressed>(ArrowKey::LEFT));
            }
            if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_UP)
            {
                eventManager.enqueueEvent(std::make_unique<ArrowKeyPressed>(ArrowKey::UP));
            }
            if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_DOWN)
            {
                eventManager.enqueueEvent(std::make_unique<ArrowKeyPressed>(ArrowKey::DOWN));
            }
        }
    }

    bool isKeyPressed(Keyboard key) const override
    {
        auto keys = SDL_GetKeyboardState(nullptr);

        switch (key)
        {
        case Keyboard::A:
            return keys[SDL_SCANCODE_A];
            break;
        case Keyboard::B:
            return keys[SDL_SCANCODE_B];
            break;
        case Keyboard::C:
            return keys[SDL_SCANCODE_C];
            break;
        case Keyboard::D:
            return keys[SDL_SCANCODE_D];
            break;
        case Keyboard::E:
            return keys[SDL_SCANCODE_E];
            break;
        case Keyboard::F:
            return keys[SDL_SCANCODE_F];
            break;
        case Keyboard::G:
            return keys[SDL_SCANCODE_G];
            break;
        case Keyboard::H:
            return keys[SDL_SCANCODE_H];
            break;
        case Keyboard::I:
            return keys[SDL_SCANCODE_I];
            break;
        case Keyboard::J:
            return keys[SDL_SCANCODE_J];
            break;
        case Keyboard::K:
            return keys[SDL_SCANCODE_K];
            break;
        case Keyboard::L:
            return keys[SDL_SCANCODE_L];
            break;
        case Keyboard::M:
            return keys[SDL_SCANCODE_M];
            break;
        case Keyboard::N:
            return keys[SDL_SCANCODE_N];
            break;
        case Keyboard::O:
            return keys[SDL_SCANCODE_O];
            break;
        case Keyboard::P:
            return keys[SDL_SCANCODE_P];
            break;
        case Keyboard::Q:
            return keys[SDL_SCANCODE_Q];
            break;
        case Keyboard::R:
            return keys[SDL_SCANCODE_R];
            break;
        case Keyboard::S:
            return keys[SDL_SCANCODE_S];
            break;
        case Keyboard::T:
            return keys[SDL_SCANCODE_T];
            break;
        case Keyboard::U:
            return keys[SDL_SCANCODE_U];
            break;
        case Keyboard::V:
            return keys[SDL_SCANCODE_V];
            break;
        case Keyboard::W:
            return keys[SDL_SCANCODE_W];
            break;
        case Keyboard::X:
            return keys[SDL_SCANCODE_X];
            break;
        case Keyboard::Y:
            return keys[SDL_SCANCODE_Y];
            break;
        case Keyboard::Z:
            return keys[SDL_SCANCODE_Z];
            break;
        case Keyboard::RIGHT:
            return keys[SDL_SCANCODE_RIGHT];
            break;
        case Keyboard::LEFT:
            return keys[SDL_SCANCODE_LEFT];
            break;
        case Keyboard::UP:
            return keys[SDL_SCANCODE_UP];
            break;
        case Keyboard::DOWN:
            return keys[SDL_SCANCODE_DOWN];
            break;
        default:
            break;
        }
        throw std::runtime_error{"The given key doesn't exist in this backend!"};
    }
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

    std::unique_ptr<IRendererPrimitive> rendererPrimitive() override
    {
        auto rendererPrimitive{std::make_unique<RendererPrimitive>(wnd)};
        renderer = rendererPrimitive->m_renderer.get();
        return rendererPrimitive;
    }

    std::unique_ptr<IWindowPrimitive> windowPrimitive() override
    {
        auto wndPrimitive{std::make_unique<WindowPrimitive>()};
        wnd = wndPrimitive->m_window.get();
        return wndPrimitive;
    }

    using RendererBackendSDL = std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)>;
    struct RendererPrimitive : IRendererPrimitive
    {
        RendererBackendSDL m_renderer;
        RendererPrimitive(SDL_Window *wnd) : m_renderer(makeUniqueRenderer(wnd))
        {
        }

      private:
        RendererBackendSDL makeUniqueRenderer(SDL_Window *wnd)
        {
            auto r{SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)};
            if (r == nullptr)
            {
                throw std::runtime_error{SDL_GetError()};
            }

            return RendererBackendSDL{r, [](SDL_Renderer *_r) {
                                          if (_r)
                                          {
                                              SDL_DestroyRenderer(_r);
                                          }
                                      }};
        }
    };
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
