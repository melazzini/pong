#include "Drawable.h"
#include "EventManagementInterface.h"
#include "EventUtils.h"
#include "GameBase.h"
#include "GameObject.h"
#include "Interfaces.h"
#include "components/Component.h"
#include "gmock/gmock.h"
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

struct ADummyComponentManager : ComponentManager
{
    MOCK_METHOD(void, registerComponent, (Component *), (override));
};
struct AGameBase : testing::Test
{
    DummyWindow window;
    DummyRenderer renderer;
    DummyEventManager eventManager;
    GameBase::GameBackend backend;
    std::unique_ptr<GameBase> game;
    NiceMock<ADummyComponentManager> componenManager;
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

TEST_F(AGameBase, PollsTheSystemEventsWhenItHandlesInput)
{
    EXPECT_CALL(eventManager, pollEvents);
    game->handleInput();
}

TEST_F(AGameBase, KnowsIfItsRunning)
{
    game->setRunning(true);
    ASSERT_TRUE(game->isRunning());
    game->setRunning(false);
    ASSERT_FALSE(game->isRunning());
}

struct ADummyComponent : Component
{
    ADummyComponent(GameObject *owner, ComponentManager *manager) : Component(owner, manager)
    {
    }
};

struct DummyGameObject : GameObject
{
    DummyGameObject(ComponentManager *manager_)
    {
        addComponent<ADummyComponent>(this, manager_);
    }

    ADummyComponent *getDummyComponentSpy() const
    {
        return dynamic_cast<ADummyComponent *>(m_components.back().get());
    }
};

TEST_F(AGameBase, CanAddGameObjects)
{
    ASSERT_FALSE(game->hasGameObject("dummyGameObject"));
    game->addGameObject(std::make_unique<DummyGameObject>(&componenManager), "dummyGameObject");
    ASSERT_TRUE(game->hasGameObject("dummyGameObject"));
}

TEST_F(AGameBase, ReturnsFalseIfYouPassItANullGameObject)
{
    ASSERT_FALSE(game->addGameObject(nullptr, "dummy-dummyGameObject"));
}

TEST_F(AGameBase, ReturnsFalseIfYouPassItADuplicatedTag)
{
    game->addGameObject(std::make_unique<DummyGameObject>(&componenManager), "dummyGameObject");
    ASSERT_FALSE(game->addGameObject(std::make_unique<DummyGameObject>(&componenManager), "dummyGameObject"));
}

TEST_F(AGameBase, DoesntStoreTheGameObjectIfItReturnsFalse)
{
    ASSERT_FALSE(game->addGameObject(nullptr, "dummy-dummy"));
    ASSERT_FALSE(game->hasGameObject("dummy-dummy"));
}

TEST_F(AGameBase, PassesEachComponentToItsCorrespondingComponentManagerForTheGivenGameObject)
{
    auto gameObject = std::make_unique<DummyGameObject>(&componenManager);
    EXPECT_CALL(componenManager, registerComponent)
        .WillOnce(
            [spy = gameObject->getDummyComponentSpy()](Component *component_) { ASSERT_THAT(component_, Eq(spy)); });

    game->addGameObject(std::move(gameObject), "dummyGameObject");
}

TEST_F(AGameBase, RegistersTheComponentManagersOfTheGivenGameObject)
{
    auto gameObject = std::make_unique<DummyGameObject>(&componenManager);
    ASSERT_FALSE(game->hasComponentManager(&componenManager));
    game->addGameObject(std::move(gameObject), "dummyGameObject");
    ASSERT_TRUE(game->hasComponentManager(&componenManager));
}

TEST_F(AGameBase, CanRemoveAllTheComponentManagers)
{
    auto gameObject = std::make_unique<DummyGameObject>(&componenManager);
    game->addGameObject(std::move(gameObject), "dummyGameObject");
    auto managersCount = game->managers().size();
    ASSERT_THAT(game->managers().size(), Gt(0));
    game->removeAllManagers();
    ASSERT_THAT(game->managers().size(), Eq(0));
}

TEST_F(AGameBase, OnlyRegisterOneInstanceOfAComponentManager)
{
    game->addGameObject(std::make_unique<DummyGameObject>(&componenManager), "dummyGameObject1");
    game->addGameObject(std::make_unique<DummyGameObject>(&componenManager), "dummyGameObject2");
    auto managersCount = game->managers().size();
    ASSERT_THAT(game->managers().size(), Eq(1));
}