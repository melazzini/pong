#pragma once

#include "IComponent.h"

class ComponentManager : public IComponentManager
{
  public:
    ComponentManager(bool (*componentValidator)(IComponent *) = [](IComponent *) { return true; });

    bool registerComponent(IComponent *component) override;

    bool hasComponent(IComponent *component) const override;

    void updateComponents(uint32_t deltatime) override;

    void destroyComponents() override;

  protected:
    bool (*m_componentValidator)(IComponent *);
    std::vector<IComponent *> m_components;
};
