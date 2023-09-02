#pragma once
#include "Interfaces.h"

class Window : IWindow
{
  public:
    void clear(glm::u8vec4 color) override;

    void present() override;

    static Window *getInstance(IBackendContext *engine);

  private:
    explicit Window(IBackendContext *);
    std::unique_ptr<IWindowPrimitive> m_primitive;
};
