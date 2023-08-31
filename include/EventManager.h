#pragma once
#include "BackendContextInterface.h"
#include "EventManagementInterface.h"
#include <functional>
#include <list>
#include <memory>
#include <stdexcept>
#include <vector>
struct CallbackEventListener : IListener
{
    CallbackEventListener(EventType eventType, std::function<void(const IEvent &)> handler)
        : m_eventType{eventType}, m_handler{std::move(handler)}
    {
    }

    EventType eventType() const override
    {
        return m_eventType;
    }

    void onEvent(const IEvent &event) override
    {
        validateHandler(m_handler);
        std::invoke(m_handler, event);
    }

  private:
    EventType m_eventType;
    std::function<void(const IEvent &)> m_handler;

    void validateHandler(const std::function<void(const IEvent &)> &handler)
    {
        if (!handler)
        {
            throw std::runtime_error{"This event listener has no handler!"};
        }
    }
};

class EventManager : public IEventManager
{
  public:
    static EventManager *getInstance(backendContext::IEventManagerPrimitiveProvider *provider);

    void registerListener(IListener *listener) override;

    std::unique_ptr<CallbackEventListener> registerListener(EventType type,
                                                            std::function<void(const IEvent &)> callback);

    [[nodiscard]] bool isListenerRegistered(IListener *listener) const override;

    [[nodiscard]] bool eventQueueHasEventType(EventType eventType) const override;

    [[nodiscard]] bool isEventQueueEmpty() const override;

    void pollEvents() override;

    void enqueueEvent(std::unique_ptr<IEvent> event) override;

    void dispatchEvents() override;

    void clearEventQueue() noexcept;

    void removeAllEventListeners() noexcept;

    bool hasEventListeners() const noexcept;

  private:
    EventManager(backendContext::IEventManagerPrimitiveProvider *contextProvider);
    EventManager(const EventManager *) = delete;
    EventManager(EventManager &&) = delete;
    EventManager &operator=(const EventManager &) = delete;
    EventManager &operator=(EventManager &&) = delete;

    std::unique_ptr<IEventManagerPrimitive> m_primitive;
    std::vector<IListener *> m_listeners;
    std::list<std::unique_ptr<IEvent>> m_eventQueue;

  private:
    void validateListener(IListener *listener);
    void validateEvent(const std::unique_ptr<IEvent> &listener);
    std::unique_ptr<IEventManagerPrimitive> buildPrimitive(
        backendContext::IEventManagerPrimitiveProvider *contextProvider);
    void sendEventsToListeners();
    void pushBackListener(IListener *listener);
    void pushBackEvent(std::unique_ptr<IEvent> event);
    static void validateBackend(backendContext::IEventManagerPrimitiveProvider *contextProvider);
};

