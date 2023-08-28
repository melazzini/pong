#include "../include/EventManager.h"
#include "Interfaces.h"
#include <algorithm>
#include <memory>
#include <stdexcept>

void EventManager::registerListener(IListener *listener)
{
    validateListener(listener);
    pushBackListener(listener);
}
bool EventManager::isListenerRegistered(IListener *listener) const
{
    return std::find(std::begin(m_listeners), std::end(m_listeners), listener) != std::end(m_listeners);
}
bool EventManager::eventQueueHasEventType(EventType eventType) const
{
    return std::find_if(std::begin(m_eventQueue), std::end(m_eventQueue), [eventType](const auto &event) {
               return event->eventType() == eventType;
           }) != std::end(m_eventQueue);
}
bool EventManager::isEventQueueEmpty() const
{
    return m_eventQueue.empty();
}

void EventManager::pollEvents()
{
}
void EventManager::enqueueEvent(std::unique_ptr<IEvent> event)
{
    validateEvent(event);
    pushBackEvent(std::move(event));
}
void EventManager::dispatchEvents()
{
    sendEventsToListeners();
    clearEventQueue();
}

void EventManager::validateEvent(const std::unique_ptr<IEvent> &event)
{
    if (event == nullptr)
    {
        throw std::runtime_error{"The received event was nullptr"};
    }
}
void EventManager::validateListener(IListener *listener)
{
    if (listener == nullptr)
    {
        throw std::runtime_error{"The received event listener was nullptr"};
    }
}
void EventManager::sendEventsToListeners()
{
    for (auto &event : m_eventQueue)
    {
        for (auto listener : m_listeners)
        {
            if (listener->eventType() == event->eventType())
            {
                listener->onEvent(std::move(event));
            }
        }
    }
}
void EventManager::clearEventQueue()
{
    m_eventQueue.clear();
}

void EventManager::pushBackListener(IListener *listener)
{
    m_listeners.push_back(listener);
}

void EventManager::pushBackEvent(std::unique_ptr<IEvent> event)
{
    m_eventQueue.push_back(std::move(event));
}
