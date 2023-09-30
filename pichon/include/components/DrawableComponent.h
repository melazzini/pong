#pragma once
#include "Drawable.h"
#include "Interfaces.h"
#include "TransformComponent.h"
#include "components/Component.h"
#include <iostream>
struct DrawableComponent;
class DrawableComponentManagerBase : public IOutputComponentManager
{
  public:
    DrawableComponentManagerBase(IRenderer *renderer) : m_renderer{renderer}
    {
    }

    void draw(Drawable *drawable)
    {
        m_renderer->render(drawable);
    }

    void output() override;

    void updateComponents(uint32_t deltatime) override;

    bool hasComponent(IComponent *component) const override;

    bool registerComponent(IComponent *componet) override;

    void destroyComponents() override;

  private:
    IRenderer *m_renderer;
    std::vector<DrawableComponent *> m_components;
};

class DrawableComponent : public Component
{
  public:
    DrawableComponent(GameObject *owner, DrawableComponentManagerBase *manager)
        : Component(owner, manager), m_manager{manager}, m_drawable{nullptr}
    {
    }

    // maybe in the future you can perform animations from here
    void update(uint32_t deltaTime) override
    {
    }

    virtual void draw()
    {
        if (m_drawable)
        {
            m_manager->draw(m_drawable);
        }
    }

  protected:
    DrawableComponentManagerBase *m_manager;
    Drawable *m_drawable;
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

