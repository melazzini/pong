#include "Drawable.h"
#include "EventManagementInterface.h"
#include "EventUtils.h"
#include "Game.h"
#include "GameObject.h"
#include "Interfaces.h"
#include "RectangularGeometry.h"
#include "components/Component.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <utility>

using testing::Eq;
using testing::Gt;
using testing::InSequence;
using testing::Mock;
using testing::Ne;
using testing::NiceMock;

struct DummyWindow : IWindow
{
    MOCK_METHOD(void, clear, (glm::u8vec4), (override));
    MOCK_METHOD(void, present, (), (override));
};

struct DummyRenderer : IRenderer
{
    MOCK_METHOD(void, render, (Drawable *), (override));
    MOCK_METHOD(IRendererPrimitive *, primitive, (), (override));
};

struct DummyEventManager : IEventManager
{
    MOCK_METHOD(void, registerListener, (IListener *), (override));
    MOCK_METHOD(bool, isListenerRegistered, (IListener *), (const override));
    MOCK_METHOD(bool, eventQueueHasEventType, (EventType), (const override));
    MOCK_METHOD(bool, isEventQueueEmpty, (), (const override));
    MOCK_METHOD(void, pollEvents, (), (override));
    MOCK_METHOD(void, enqueueEvent, (std::unique_ptr<IEvent>), (override));
    MOCK_METHOD(void, dispatchEvents, (), (override));
};

struct AGameBase : testing::Test
{
    DummyWindow window;
    DummyRenderer renderer;
    DummyEventManager eventManager;
    GameBase::GameBackend backend;
    std::unique_ptr<GameBase> game;
    void SetUp() override
    {
        backend.window = &window;
        backend.renderer = &renderer;
        backend.eventManager = &eventManager;
        game = std::make_unique<GameBase>(&backend);
    }
};

TEST_F(AGameBase, ClearsAndThenShowsTheNewWindowWhenItOutputsContent)
{
    InSequence s;
    EXPECT_CALL(window, clear);
    EXPECT_CALL(window, present);
    game->output();
    Mock::VerifyAndClearExpectations(&window);
}
