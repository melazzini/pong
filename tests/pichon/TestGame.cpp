#include "Game.h"
#include "GameObject.h"
#include "RectangularGeometry.h"
#include "components/Component.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <utility>

using testing::Eq;
using testing::Mock;
using testing::Ne;
using testing::NiceMock;

TEST(AGame, IsASingleton)
{
    Game *game1 = Game::getInstance();
    Game *game2 = Game::getInstance();
    ASSERT_TRUE(game1 != nullptr);
    ASSERT_THAT(game1, Eq(game2));
}

struct ADummyComponentManager : ComponentManager
{
    MOCK_METHOD(void, registerComponent, (Component *), (override));
};

struct TheGame : testing::Test
{
    Game *game{};
    NiceMock<ADummyComponentManager> componenManager;
    void SetUp() override
    {
        game = Game::getInstance();
    }
};

TEST_F(TheGame, KnowsIfItsRunning)
{
    game->setRunning(true);
    ASSERT_TRUE(game->isRunning());
    game->setRunning(false);
    ASSERT_FALSE(game->isRunning());
}

TEST_F(TheGame, CanChangeItsWindowSize)
{
    ASSERT_THAT(game->windowSize(), Ne(RectangularGeometry{200, 200}));
    game->setWindowSize(RectangularGeometry{200, 200});
    ASSERT_THAT(game->windowSize(), Eq(RectangularGeometry{200, 200}));
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

TEST_F(TheGame, CanAddGameObjects)
{
    ASSERT_FALSE(game->hasGameObject("dummyGameObject"));
    game->addGameObject(std::make_unique<DummyGameObject>(&componenManager), "dummyGameObject");
    ASSERT_TRUE(game->hasGameObject("dummyGameObject"));
}

TEST_F(TheGame, ReturnsFalseIfYouPassItANullGameObject)
{
    ASSERT_FALSE(game->addGameObject(nullptr, "dummy-dummyGameObject"));
}
TEST_F(TheGame, ReturnsFalseIfYouPassItADuplicatedTag)
{
    game->addGameObject(std::make_unique<DummyGameObject>(&componenManager), "dummyGameObject");
    ASSERT_FALSE(game->addGameObject(std::make_unique<DummyGameObject>(&componenManager), "dummyGameObject"));
}

TEST_F(TheGame, DoesntStoreTheGameObjectIfItReturnsFalse)
{
    ASSERT_FALSE(game->addGameObject(nullptr, "dummy-dummy"));
    ASSERT_FALSE(game->hasGameObject("dummy-dummy"));
}

TEST_F(TheGame, PassesEachComponentToItsCorrespondingComponentManagerForTheGivenGameObject)
{
    auto gameObject = std::make_unique<DummyGameObject>(&componenManager);
    EXPECT_CALL(componenManager, registerComponent)
        .WillOnce(
            [spy = gameObject->getDummyComponentSpy()](Component *component_) { ASSERT_THAT(component_, Eq(spy)); });

    game->addGameObject(std::move(gameObject), "dummyGameObject10");
}
