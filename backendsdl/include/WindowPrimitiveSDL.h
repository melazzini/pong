#pragma once
#include "IPrimitives.h"
#include <memory>
struct SDL_Window;

using WindowBackendSDL = std::unique_ptr<SDL_Window, void (*)(SDL_Window *)>;
struct WindowPrimitive : IWindowPrimitive
{
    WindowBackendSDL m_window;
    WindowPrimitive();
    void clearWindow(glm::u8vec4 color) override;
    void updateWindow() override;

  private:
    WindowBackendSDL makeUniqueWindow();
};
