#include "GameObject.h"
#include "GameObjectsManager.h"
#include "components/Component.h"
#include "gmock/gmock.h"
#include <cstdlib>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using testing::Eq;
using testing::Mock;

struct MyDummyComponentManager : ComponentManager
{
};

struct MyMockComponentManager : ComponentManager
{
    MOCK_METHOD(void, update, (uint32_t), (override));
};

struct MyDummyComponent : IComponent
{
    void setManager(ComponentManager *manager_)
    {
        _manager = manager_;
    }

    ComponentManager *manager() const override
    {
        return _manager;
    }

    void update(uint32_t) override
    {
    }

    ComponentManager *_manager;
};

struct AMockComponent : IComponent
{
    MOCK_METHOD(void, update, (uint32_t), (override));
    MOCK_METHOD(ComponentManager *, manager, (), (const override));
};

struct TheGameObjectsManager : testing::Test
{
    GameObjectsManager gameObjectsManager;
    std::unique_ptr<GameObject> gameObject;
    const std::string dummyTag{"DummyTag"};
    const std::string existingGameObjectDummyTag{"ExistingGameObjectDummyTag"};
    MyDummyComponentManager myDummyComponentManager;
    MyMockComponentManager myMockComponentManager;
    const std::string aSecondDummyTag{"DummyTag2"};
    uint32_t dummyDeltaTime{10};
    void SetUp() override
    {
        gameObjectsManager.addGameObject(std::make_unique<GameObject>(), existingGameObjectDummyTag);
        gameObject = std::make_unique<GameObject>();
    }
};

TEST_F(TheGameObjectsManager, CanAddGameObjects)
{
    ASSERT_FALSE(gameObjectsManager.hasGameObject(dummyTag));
    gameObjectsManager.addGameObject(std::make_unique<GameObject>(), dummyTag);
    ASSERT_TRUE(gameObjectsManager.hasGameObject(dummyTag));
}

TEST_F(TheGameObjectsManager, RefusesToAddNullGameObjects)
{
    ASSERT_FALSE(gameObjectsManager.hasGameObject(dummyTag));
    gameObjectsManager.addGameObject(nullptr, dummyTag);
    ASSERT_FALSE(gameObjectsManager.hasGameObject(dummyTag));
}

TEST_F(TheGameObjectsManager, CannotAddAGameObjectWithDupplicatedTag)
{
    gameObjectsManager.addGameObject(std::make_unique<GameObject>(), dummyTag);
    ASSERT_FALSE(gameObjectsManager.addGameObject(std::make_unique<GameObject>(), dummyTag));
}

TEST_F(TheGameObjectsManager, CanRemoveExistingGameObjects)
{
    ASSERT_TRUE(gameObjectsManager.hasGameObject(existingGameObjectDummyTag));
    ASSERT_TRUE(gameObjectsManager.removeGameObject(existingGameObjectDummyTag));
    ASSERT_FALSE(gameObjectsManager.hasGameObject(existingGameObjectDummyTag));
}

TEST_F(TheGameObjectsManager, GetsTheComponentManagersFromTheComponentsOfTheGameObjectAdded)
{
    auto component = gameObject->addComponent<AMockComponent>();
    EXPECT_CALL(*component, manager());
    gameObjectsManager.addGameObject(std::move(gameObject), dummyTag);
    Mock::AllowLeak(component);
    Mock::VerifyAndClearExpectations(component);
}

TEST_F(TheGameObjectsManager, CannotAddAnExistingComponentManager)
{
    auto myDummyComponent{gameObject->addComponent<MyDummyComponent>()};
    myDummyComponent->setManager(&myDummyComponentManager);
    gameObjectsManager.addGameObject(std::move(gameObject), dummyTag);
    ASSERT_TRUE(gameObjectsManager.hasComponentManager(&myDummyComponentManager));

    auto aSecondGameObject{std::make_unique<GameObject>()};
    auto aSecondDummyComponent{aSecondGameObject->addComponent<MyDummyComponent>()};
    aSecondDummyComponent->setManager(&myDummyComponentManager);
    gameObjectsManager.addGameObject(std::move(aSecondGameObject), aSecondDummyTag);

    const auto &listOfComponentManagers{gameObjectsManager.listOfComponentManagers()};
    ASSERT_THAT(listOfComponentManagers.count(&myDummyComponentManager), Eq(1));
}

TEST_F(TheGameObjectsManager, UsesTheComponentManagersToUpdateTheGameObjectComponents)
{
    auto myDummyComponent{gameObject->addComponent<MyDummyComponent>()};
    myDummyComponent->setManager(&myMockComponentManager);
    gameObjectsManager.addGameObject(std::move(gameObject), dummyTag);
    EXPECT_CALL(myMockComponentManager, update(dummyDeltaTime));
    gameObjectsManager.updateGameObjects(dummyDeltaTime);
}
