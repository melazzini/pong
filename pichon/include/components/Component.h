#pragma once

struct Component;
struct ComponentManager
{
    virtual void registerComponent(Component *)
    {
    }

    virtual void update(float deltatime)
    {
    }

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
