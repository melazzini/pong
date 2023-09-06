#include "EventManagementInterface.h"
#include "EventManager.h"
#include "EventUtils.h"
#include "MockEventManager.h"
#include "components/InputComponent.h"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using testing::Eq;
using testing::Ne;
using testing::Return;

struct AnInputComponentManager : testing::Test
{
    MockEventManager eventManager{};
};

TEST_F(AnInputComponentManager, RequiresAnEventManager)
{
    InputComponentManagerBase componentManager{&eventManager};
}

struct DummyListener : IListener
{
    EventType eventType() const override
    {
        return EventType(-1);
    }

    void onEvent(const IEvent &event) override
    {
    }
};

TEST_F(AnInputComponentManager, UsesItsEventManagerToRegisterListeners)
{
    DummyListener listener;
    InputComponentManagerBase componentManager{&eventManager};
    EXPECT_CALL(eventManager, registerListener);
    componentManager.registerListener(&listener);
}
