#include "EventManagementInterface.h"
#include "EventUtils.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
struct MockEventManager : IEventManager
{
    MOCK_METHOD(void, registerListener, (IListener *), (override));
    MOCK_METHOD(bool, isListenerRegistered, (IListener *), (const override));
    MOCK_METHOD(bool, isKeyPressed, (Keyboard), (const override));
    MOCK_METHOD(bool, eventQueueHasEventType, (EventType), (const override));
    MOCK_METHOD(bool, isEventQueueEmpty, (), (const override));
    MOCK_METHOD(void, pollEvents, (), (override));
    MOCK_METHOD(void, enqueueEvent, (std::unique_ptr<IEvent>), (override));
    MOCK_METHOD(void, dispatchEvents, (), (override));
};
