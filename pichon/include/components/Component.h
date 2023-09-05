#pragma once

struct ComponentManager
{
    virtual ~ComponentManager() = default;
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
