#pragma once
#include "Interfaces.h"

class Window : IWindow
{
  public:
    void clear(glm::u8vec4 color) override
    {
    }

    void present(IRenderer *) override
    {
    }

    static Window *getInstance(IBackendContext *engine);

  private:
    Window() = default;
};
