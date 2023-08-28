#include "gmock/gmock.h"
#include <algorithm>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iterator>
#include <list>
#include <memory>
#include <vector>

using testing::Eq;
using testing::Ne;

enum class EventType
{
};

class Event
{
  public:
    Event(EventType type) : m_type{type}
    {
    }

    EventType eventType() const
    {
        return m_type;
    }

  private:
    EventType m_type;
};

struct IListener
{
    virtual EventType eventType() const = 0;

    virtual void onEvent(std::unique_ptr<Event> event) = 0;
};

struct DummyListener : IListener
{

    DummyListener(EventType eventType) : m_eventType{eventType}
    {
    }

    EventType eventType() const override
    {
        return m_eventType;
    }

    MOCK_METHOD(void, onEvent, (std::unique_ptr<Event>), (override));

  private:
    EventType m_eventType;
};
struct EventManager
{
    void registerListener(IListener *listener)
    {
        m_listeners.push_back(listener);
    }

    bool listenerIsRegistered(IListener *listener) const
    {
        return std::find(std::begin(m_listeners), std::end(m_listeners), listener) != std::end(m_listeners);
    }

    bool eventQueueHasEventType(EventType eventType) const
    {

        return std::find_if(std::begin(m_eventQueue), std::end(m_eventQueue), [eventType](const auto &event) {
                   return event->eventType() == eventType;
               }) != std::end(m_eventQueue);
    }

    bool isEventQueueEmpty() const
    {
        return m_eventQueue.empty();
    }

    void pollEvents()
    {
    }

    void enqueueEvent(std::unique_ptr<Event> event)
    {
        m_eventQueue.push_back(std::move(event));
    }

    void dispatchEvents()
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

  private:
    std::vector<IListener *> m_listeners;
    std::list<std::unique_ptr<Event>> m_eventQueue;
};

struct TheEventManager : testing::Test
{
    EventType dummyEventType{EventType(-1)};
    EventManager eventManager;
    DummyListener dummyListener{dummyEventType};
    std::unique_ptr<Event> dummyEvent{std::make_unique<Event>(dummyEventType)};
    Event *dummyEventSpy{dummyEvent.get()};
};

TEST_F(TheEventManager, CanRegisterListeners)
{
    ASSERT_FALSE(eventManager.listenerIsRegistered(&dummyListener));
    eventManager.registerListener(&dummyListener);
    ASSERT_TRUE(eventManager.listenerIsRegistered(&dummyListener));
}

TEST_F(TheEventManager, CanEnqueueNewEvents)
{
    ASSERT_TRUE(dummyEvent->eventType() == dummyEventType);
    ASSERT_FALSE(eventManager.eventQueueHasEventType(dummyEvent->eventType()));
    eventManager.enqueueEvent(std::move(dummyEvent));
    ASSERT_TRUE(eventManager.eventQueueHasEventType(dummyEventType));
}

TEST_F(TheEventManager, NotifiesAListenerAboutACorrespondingEvent)
{
    DummyListener aDummyListenerForEventType{dummyEventType};
    eventManager.registerListener(&aDummyListenerForEventType);
    eventManager.enqueueEvent(std::move(dummyEvent));

    EXPECT_CALL(aDummyListenerForEventType, onEvent)
        .WillOnce([dummyEventTypeCopy = dummyEventType](const std::unique_ptr<Event> &event) {
            ASSERT_TRUE(event->eventType() == dummyEventTypeCopy);
        });

    eventManager.dispatchEvents();
}

struct TheEventManagerQueue : TheEventManager
{
    testing::NiceMock<DummyListener> aDummyListenerForEventType{dummyEventType};
    void SetUp()
    {
        eventManager.registerListener(&aDummyListenerForEventType);
        eventManager.enqueueEvent(std::move(dummyEvent));
    }
};

TEST_F(TheEventManagerQueue, IsEmptyAfterDispachingTheEvents)
{
    ASSERT_FALSE(eventManager.isEventQueueEmpty());
    eventManager.dispatchEvents();
    ASSERT_TRUE(eventManager.isEventQueueEmpty());
}
