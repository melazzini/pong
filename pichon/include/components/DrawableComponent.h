#pragma once
#include "Drawable.h"
#include "Interfaces.h"
#include "TransformComponent.h"
#include "components/Component.h"
#include <iostream>

class DrawableComponentManagerBase : public ComponentManager
{
  public:
    DrawableComponentManagerBase(IRenderer *renderer) : m_renderer{renderer}
    {
    }

    void draw(Drawable *drawable)
    {
        m_renderer->render(drawable);
    }

  private:
    IRenderer *m_renderer;
};

class DrawableComponent : public Component
{
  public:
    DrawableComponent(GameObject *owner, ComponentManager *manager) : Component(owner, manager)
    {
    }

    void update(float deltaTime) override
    {
        std::cout << "DrawableComponent: " << __FUNCTION__ << std::endl;
    }
};

class DrawableComponentManager : public DrawableComponentManagerBase
{
  public:
    static DrawableComponentManager *getInstance(IRenderer *renderer);

  private:
    explicit DrawableComponentManager(IRenderer *renderer) : DrawableComponentManagerBase(renderer)
    {
    }
};

