#pragma once
#include "EventUtils.h"
#include <memory>

struct IEvent
{
    [[nodiscard]] virtual EventType eventType() const = 0;
    virtual ~IEvent() = default;
};

struct IListener
{
    [[nodiscard]] virtual EventType eventType() const = 0;

    virtual void onEvent(const IEvent &event) = 0;
    virtual ~IListener() = default;
};

struct IEventManager
{
    virtual void registerListener(IListener *) = 0;
    [[nodiscard]] virtual bool isListenerRegistered(IListener *listener) const = 0;
    [[nodiscard]] virtual bool eventQueueHasEventType(EventType eventType) const = 0;
    [[nodiscard]] virtual bool isEventQueueEmpty() const = 0;
    [[nodiscard]] virtual bool isKeyPressed(Keyboard letter) const = 0;
    virtual void pollEvents() = 0;
    virtual void enqueueEvent(std::unique_ptr<IEvent> event) = 0;
    virtual void dispatchEvents() = 0;
    virtual ~IEventManager() = default;
};

