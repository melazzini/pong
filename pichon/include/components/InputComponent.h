#pragma once
#include "Component.h"
#include "EventManagementInterface.h"
#include "EventManager.h"
class InputComponentManagerBase : public ComponentManager
{
  public:
    InputComponentManagerBase(IEventManager *eventManager) : m_eventManager(eventManager)
    {
    }

    void registerListener(IListener *listener)
    {
        m_eventManager->registerListener(listener);
    }

  private:
    IEventManager *m_eventManager;
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
    InputComponent(GameObject *owner, ComponentManager *manager) : Component(owner, manager)
    {
    }
    void update(float deltatime) override
    {
    }
};
