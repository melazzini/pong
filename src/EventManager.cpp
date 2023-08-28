#include "../include/EventManager.h"
#include <algorithm>
#include <stdexcept>

void EventManager::registerListener(IListener *listener)
{
    if (listener == nullptr)
    {
        throw std::runtime_error{"The received event listener was nullptr"};
    }
    m_listeners.push_back(listener);
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
    if (event == nullptr)
    {
        throw std::runtime_error{"The received event was nullptr"};
    }

    m_eventQueue.push_back(std::move(event));
}
void EventManager::dispatchEvents()
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
    m_eventQueue.clear();
}
