#pragma once
#include "Interfaces.h"
#include <list>
#include <vector>

class EventManager : public IEventManger
{
  public:
    void registerListener(IListener *listener) override;

    [[nodiscard]] bool isListenerRegistered(IListener *listener) const override;

    [[nodiscard]] bool eventQueueHasEventType(EventType eventType) const override;

    [[nodiscard]] bool isEventQueueEmpty() const override;

    void pollEvents() override;

    void enqueueEvent(std::unique_ptr<IEvent> event) override;

    void dispatchEvents() override;

  private:
    std::vector<IListener *> m_listeners;
    std::list<std::unique_ptr<IEvent>> m_eventQueue;
};

