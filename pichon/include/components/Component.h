#pragma once
#include <cstdint>
#include <vector>

struct IComponent;

class ComponentManager
{
  public:
    ComponentManager(bool (*componentValidator)(IComponent *) = [](IComponent *) { return true; })
        : m_componentValidator(componentValidator)
    {
    }

    virtual void registerComponent(IComponent *component)
    {
        if (m_componentValidator(component))
        {
            m_components.push_back(component);
        }
    }

    bool hasComponent(IComponent *component) const;

    virtual void update(uint32_t deltatime);

    virtual void destroy()
    {
    }

    virtual ~ComponentManager() = default;

  protected:
    bool (*m_componentValidator)(IComponent *);
    std::vector<IComponent *> m_components;
};

struct OutputComponentManager : ComponentManager
{
    virtual void output() = 0;
};

struct GameObject;

struct IComponent
{
    ~IComponent() = default;
    virtual void update(uint32_t deltatime) = 0;
    virtual ComponentManager *manager() const = 0;
};

class Component : public IComponent
{
  public:
    Component(GameObject *owner, ComponentManager *manager);
    virtual void update(uint32_t deltaTime) override
    {
    }
    virtual ComponentManager *manager() const override;

  private:
    [[nodiscard]] GameObject *validateOwner(GameObject *owner);
    [[nodiscard]] ComponentManager *validateManager(ComponentManager *manager);

  private:
    ComponentManager *m_manager;
};
