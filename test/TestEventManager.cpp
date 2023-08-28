#include "Event.h"
#include "EventManager.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using testing::Eq;
using testing::Ne;

struct DummyListener : IListener
{
    DummyListener(EventType eventType) : m_eventType{eventType}
    {
    }

    EventType eventType() const override
    {
        return m_eventType;
    }

    MOCK_METHOD(void, onEvent, (std::unique_ptr<IEvent>), (override));

  private:
    EventType m_eventType;
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
    ASSERT_FALSE(eventManager.isListenerRegistered(&dummyListener));
    eventManager.registerListener(&dummyListener);
    ASSERT_TRUE(eventManager.isListenerRegistered(&dummyListener));
}

TEST_F(TheEventManager, ThrowsIfYouTryToRegisterANullListener)
{
    ASSERT_THROW(eventManager.registerListener(nullptr), std::runtime_error);
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
        .WillOnce([dummyEventTypeCopy = dummyEventType](const std::unique_ptr<IEvent> &event) {
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

