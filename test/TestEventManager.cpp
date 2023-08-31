#include "EventManagementInterface.h"
#include "EventManager.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

using testing::Eq;
using testing::Mock;
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

    MOCK_METHOD(void, onEvent, (const IEvent &), (override));

  private:
    EventType m_eventType;
};

struct DummyEventManagerPrimitive : IEventManagerPrimitive
{
    MOCK_METHOD(void, pollEvents, (IEventManager &), (const override));
};

struct DummyEventManagerPrimitiveProvider : backendContext::IEventManagerPrimitiveProvider
{
    inline static DummyEventManagerPrimitive *spy{};
    std::unique_ptr<IEventManagerPrimitive> provide() const override
    {
        auto instance{std::make_unique<DummyEventManagerPrimitive>()};
        spy = instance.get();
        return instance;
    }
};

class DummyEvent : public IEvent
{
  public:
    DummyEvent(EventType type) : m_type{type}
    {
    }

    EventType eventType() const override
    {
        return m_type;
    }

  private:
    EventType m_type;
};

struct TheEventManager : testing::Test
{
    EventType dummyEventType{EventType(-1)};
    DummyListener dummyListener{dummyEventType};
    std::unique_ptr<DummyEvent> dummyEvent{std::make_unique<DummyEvent>(dummyEventType)};
    DummyEvent *dummyEventSpy{dummyEvent.get()};
    EventManager *eventManager;
    DummyEventManagerPrimitiveProvider contextProvider;
    inline static DummyEventManagerPrimitive *dummyEventPrimitiveSpy{};
    void SetUp() override
    {
        eventManager = EventManager::getInstance(&contextProvider);
        if (dummyEventPrimitiveSpy == nullptr)
        {
            dummyEventPrimitiveSpy = DummyEventManagerPrimitiveProvider::spy;
        }
    }
    void TearDown() override
    {
        eventManager->clearEventQueue();
        eventManager->removeAllEventListeners();
    }
};

TEST_F(TheEventManager, IsASingleTon)
{
    EventManager *eventManager1{EventManager::getInstance(&contextProvider)};
    EventManager *eventManager2{EventManager::getInstance(&contextProvider)};
    ASSERT_TRUE(eventManager1 != nullptr);
    ASSERT_EQ(eventManager1, eventManager2);
}

TEST_F(TheEventManager, ThrowsIfYouPassItANullptrBackendContextToGetTheInstance)
{
    ASSERT_THROW(EventManager::getInstance(nullptr), std::runtime_error);
}

TEST_F(TheEventManager, CanRegisterListeners)
{
    ASSERT_FALSE(eventManager->isListenerRegistered(&dummyListener));
    eventManager->registerListener(&dummyListener);
    ASSERT_TRUE(eventManager->isListenerRegistered(&dummyListener));
}

TEST_F(TheEventManager, ThrowsIfYouTryToRegisterANullListener)
{
    ASSERT_THROW(eventManager->registerListener(nullptr), std::runtime_error);
}

TEST_F(TheEventManager, CanEnqueueNewEvents)
{
    ASSERT_TRUE(dummyEvent->eventType() == dummyEventType);
    ASSERT_FALSE(eventManager->eventQueueHasEventType(dummyEvent->eventType()));
    eventManager->enqueueEvent(std::move(dummyEvent));
    ASSERT_TRUE(eventManager->eventQueueHasEventType(dummyEventType));
}

TEST_F(TheEventManager, ThrowsIfYouTryToEnqueANullEvent)
{
    ASSERT_THROW(eventManager->enqueueEvent(nullptr), std::runtime_error);
}
TEST_F(TheEventManager, CanClearTheEventQueue)
{
    eventManager->enqueueEvent(std::move(dummyEvent));
    ASSERT_FALSE(eventManager->isEventQueueEmpty());
    eventManager->clearEventQueue();
    ASSERT_TRUE(eventManager->isEventQueueEmpty());
}
TEST_F(TheEventManager, CanRemoveAllTheEventListeners)
{
    DummyListener aDummyListenerForEventType{dummyEventType};
    eventManager->registerListener(&aDummyListenerForEventType);
    ASSERT_TRUE(eventManager->hasEventListeners());
    eventManager->removeAllEventListeners();
    ASSERT_FALSE(eventManager->hasEventListeners());
}

TEST_F(TheEventManager, NotifiesAListenerAboutACorrespondingEvent)
{
    DummyListener aDummyListenerForEventType{dummyEventType};
    eventManager->registerListener(&aDummyListenerForEventType);
    eventManager->enqueueEvent(std::move(dummyEvent));

    EXPECT_CALL(aDummyListenerForEventType, onEvent)
        .WillOnce([dummyEventTypeCopy = dummyEventType](const IEvent &event) {
            ASSERT_TRUE(event.eventType() == dummyEventTypeCopy);
        });

    eventManager->dispatchEvents();
}

TEST_F(TheEventManager, HasAnEmptyQueueAfterDispatchingEvents)
{
    eventManager->enqueueEvent(std::move(dummyEvent));
    ASSERT_FALSE(eventManager->isEventQueueEmpty());
    eventManager->dispatchEvents();
    ASSERT_TRUE(eventManager->isEventQueueEmpty());
}

TEST_F(TheEventManager, UsesItsPrimitiveToPollTheEvents)
{
    EXPECT_CALL(*dummyEventPrimitiveSpy, pollEvents);
    eventManager->pollEvents();
    Mock::VerifyAndClearExpectations(dummyEventPrimitiveSpy);
}

TEST_F(TheEventManager, DispachesAllTheEventsWhenPolling)
{
    DummyListener aDummyListenerForEventType{dummyEventType};
    eventManager->registerListener(&aDummyListenerForEventType);
    EXPECT_CALL(*dummyEventPrimitiveSpy, pollEvents)
        .WillOnce(
            [dm = std::move(dummyEvent)](IEventManager &evtManger) mutable { evtManger.enqueueEvent(std::move(dm)); });
    EXPECT_CALL(aDummyListenerForEventType, onEvent)
        .WillOnce([dummyEventTypeCopy = dummyEventType](const IEvent &event) {
            ASSERT_TRUE(event.eventType() == dummyEventTypeCopy);
        });
    eventManager->pollEvents();
    Mock::VerifyAndClearExpectations(dummyEventPrimitiveSpy);
}

TEST_F(TheEventManager, CanReceiveALambdaAsAListener)
{
    bool theCallbackWasExecuted{false};
    auto listener_ = eventManager->registerListener(
        dummyEventType, [&theCallbackWasExecuted](const IEvent &) { theCallbackWasExecuted = true; });
    auto listener{std::unique_ptr<CallbackEventListener>(dynamic_cast<CallbackEventListener *>(listener_.release()))};
    eventManager->enqueueEvent(std::move(dummyEvent));
    eventManager->dispatchEvents();
    ASSERT_THAT(listener, Ne(nullptr));
    ASSERT_TRUE(theCallbackWasExecuted);
}

TEST(ACallbackEventListener, ThrowsIfTheCallbackIsNull)
{
    EventType dummyEventType{-1};
    CallbackEventListener listener{dummyEventType, std::function<void(const IEvent &)>{}};
    ASSERT_THROW(listener.onEvent(DummyEvent{dummyEventType}), std::runtime_error);
}
