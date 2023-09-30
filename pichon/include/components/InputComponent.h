#pragma once
#include "Component.h"
#include "EventManagementInterface.h"
#include "EventManager.h"
class InputComponentManagerBase : public IComponentManager
{
  public:
    InputComponentManagerBase(IEventManager *eventManager) : m_eventManager(eventManager)
    {
    }

    void registerListener(IListener *listener)
    {
        m_eventManager->registerListener(listener);
    }

    bool isKeyPressed(Keyboard letter)
    {
        return m_eventManager->isKeyPressed(letter);
    }

    bool registerComponent(IComponent *component) override;
    bool hasComponent(IComponent *component) const override;
    void updateComponents(uint32_t deltatime) override;
    void destroyComponents() override;

  private:
    IEventManager *m_eventManager;
    std::vector<IComponent *> m_components;
};

class InputComponentManager : public InputComponentManagerBase
{
  public:
    static InputComponentManager *getInstance(IEventManager *);

  private:
    InputComponentManager(IEventManager *eventManager) : InputComponentManagerBase{eventManager}
    {
    }
};

class InputComponent : public Component
{
  public:
    InputComponent(GameObject *owner, IComponentManager *manager) : Component(owner, manager)
    {
    }
    void update(uint32_t deltatime) override
    {
    }
};
