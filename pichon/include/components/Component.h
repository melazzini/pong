#pragma once
#include <vector>

struct Component;

class ComponentManager
{
  public:
    ComponentManager(bool (*componentValidator)(Component *) = [](Component *) { return true; })
        : m_componentValidator(componentValidator)
    {
    }

    virtual void registerComponent(Component *component)
    {
        if (m_componentValidator(component))
        {
            m_components.push_back(component);
        }
    }

    virtual void update(float deltatime);

    virtual ~ComponentManager() = default;

  protected:
    bool (*m_componentValidator)(Component *);
    std::vector<Component *> m_components;
};

struct GameObject;

class Component
{
  public:
    Component(GameObject *owner, ComponentManager *manager);

    virtual void update(float deltaTime)
    {
    }

    virtual ~Component() = default;

    ComponentManager *manager() const;

  private:
    [[nodiscard]] GameObject *validateOwner(GameObject *owner);
    [[nodiscard]] ComponentManager *validateManager(ComponentManager *manager);

  private:
    ComponentManager *m_manager;
};
