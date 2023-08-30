#pragma once
#include "Interfaces.h"
#include <list>
#include <memory>
#include <vector>

class EventManager : public IEventManager
{
  public:
    static EventManager *getInstance(backendContext::IEventManagerPrimitiveProvider *provider);

    void registerListener(IListener *listener) override;

    [[nodiscard]] bool isListenerRegistered(IListener *listener) const override;

    [[nodiscard]] bool eventQueueHasEventType(EventType eventType) const override;

    [[nodiscard]] bool isEventQueueEmpty() const override;

    void pollEvents() override;

    void enqueueEvent(std::unique_ptr<IEvent> event) override;

    void dispatchEvents() override;

    void clearEventQueue();

    void removeAllEventListeners();

    bool hasEventListeners() const;

  private:
    EventManager(backendContext::IEventManagerPrimitiveProvider *contextProvider);
    std::unique_ptr<IEventManagerPrimitive> m_primitive;
    std::vector<IListener *> m_listeners;
    std::list<std::unique_ptr<IEvent>> m_eventQueue;

  private:
    void validateListener(IListener *listener);
    void validateEvent(const std::unique_ptr<IEvent> &listener);
    void sendEventsToListeners();
    void pushBackListener(IListener *listener);
    void pushBackEvent(std::unique_ptr<IEvent> event);
};

