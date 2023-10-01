#pragma once
#include "IPrimitives.h"
#include "Interfaces.h"
#include <glm/glm.hpp>

struct SDL_Renderer;
struct RendererPrimitiveSDL;

class RectangularShapePrimitiveSDL : public IRectangularDrawablePrimitive
{
  public:
    void paintWithRendererPrimitive(IRendererPrimitive *rendererPrimitive) override;
    void setBackgroundColor(glm::u8vec4 newcolor) override;
    glm::u8vec4 backgroundColor() const override;
    void setPosition(glm::ivec2 newPosition) override;
    void setSize(glm::ivec2 newSize) override;
    glm::ivec2 size() const override;
    glm::ivec2 position() const override;

  private:
    glm::u8vec4 m_backgroundColor;
    glm::ivec2 m_position;
    glm::ivec2 m_size;
};

