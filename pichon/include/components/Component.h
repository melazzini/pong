#pragma once
#include "IComponent.h"

struct GameObject;

class Component : public IComponent
{
  public:
    Component(GameObject *owner, IComponentManager *manager);
    virtual void update(uint32_t deltaTime) override
    {
    }
    virtual IComponentManager *manager() const override;

  private:
    [[nodiscard]] GameObject *validateOwner(GameObject *owner);
    [[nodiscard]] IComponentManager *validateManager(IComponentManager *manager);

  private:
    IComponentManager *m_manager;
};
