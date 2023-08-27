#pragma once
#include "Interfaces.h"
#include <SDL2/SDL.h>
#include <SDL_video.h>
#include <memory>
#include <stdexcept>

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
            auto r{SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED)};
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
            auto wnd{SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 400,
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
