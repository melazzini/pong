#include "GameObject.h"
#include "GameObjectsManager.h"
#include "components/Component.h"
#include "gmock/gmock.h"
#include <cstdlib>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

using testing::Eq;
using testing::Mock;
using testing::NiceMock;
using testing::Return;

struct MyDummyComponentManager : ComponentManager
{
};

struct MyDummyOutputComponentManager : IOutputComponentManager
{
    void output() override
    {
    }

    void updateComponents(uint32_t deltatime) override
    {
    }

    void destroyComponents() override
    {
    }

    bool registerComponent(IComponent *) override
    {
        return false;
    }
    bool hasComponent(IComponent *) const override
    {
        return false;
    }
};

struct MyMockComponentManager : ComponentManager
{
    MOCK_METHOD(bool, registerComponent, (IComponent *), (override));
    MOCK_METHOD(void, destroyComponents, (), (override));
    MOCK_METHOD(void, updateComponents, (uint32_t), (override));
};

struct MyMockOutputComponentManager : IOutputComponentManager
{
    MOCK_METHOD(void, updateComponents, (uint32_t), (override));
    MOCK_METHOD(void, destroyComponents, (), (override));
    MOCK_METHOD(void, output, (), (override));
    MOCK_METHOD(bool, hasComponent, (IComponent *), (const override));
    MOCK_METHOD(bool, registerComponent, (IComponent *), (override));
};

struct MyDummyComponent : IComponent
{
    void setManager(IComponentManager *manager_)
    {
        _manager = manager_;
    }

    IComponentManager *manager() const override
    {
        return _manager;
    }

    void update(uint32_t) override
    {
    }

    IComponentManager *_manager;
};

struct AMockComponent : IComponent
{
    MOCK_METHOD(void, update, (uint32_t), (override));
    MOCK_METHOD(IComponentManager *, manager, (), (const override));
};

struct TheGameObjectsManager : testing::Test
{
    GameObjectsManager gameObjectsManager;
    std::unique_ptr<GameObject> gameObject;
    const std::string dummyTag{"DummyTag"};
    const std::string existingGameObjectDummyTag{"ExistingGameObjectDummyTag"};
    MyDummyComponentManager myDummyComponentManager;
    MyDummyOutputComponentManager myDummyOutputComponentManager;
    NiceMock<MyMockOutputComponentManager> myMockOutputComponentManager;
    NiceMock<MyMockComponentManager> myMockComponentManager;
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

TEST_F(TheGameObjectsManager, ThrowsIfYouAddAGameObjectWhichHasAComponentWithANullComponentManager)
{
    auto myDummyComponent{gameObject->addComponent<MyDummyComponent>()};
    myDummyComponent->setManager(nullptr);
    ASSERT_THROW(gameObjectsManager.addGameObject(std::move(gameObject), dummyTag), std::runtime_error);
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
    EXPECT_CALL(*component, manager()).WillOnce(Return(&myDummyComponentManager));
    gameObjectsManager.addGameObject(std::move(gameObject), dummyTag);
    Mock::AllowLeak(component);
    Mock::VerifyAndClearExpectations(component);
}

TEST_F(TheGameObjectsManager, GetsTheOutputComponentManagersFromTheComponentsOfTheGameObjectAdded)
{
    auto component = gameObject->addComponent<AMockComponent>();
    EXPECT_CALL(*component, manager()).WillOnce(Return(&myDummyOutputComponentManager));
    gameObjectsManager.addGameObject(std::move(gameObject), dummyTag);
    Mock::AllowLeak(component);
    Mock::VerifyAndClearExpectations(component);

    ASSERT_TRUE(gameObjectsManager.hasOutputComponentManager(&myDummyOutputComponentManager));
}

TEST_F(
    TheGameObjectsManager,
    GetsTheNonOutputComponentManagersFromTheComponentsOfTheGameObjectAddedButNotRegisterThemAsOutputComponentManagers)
{
    auto component = gameObject->addComponent<AMockComponent>();
    EXPECT_CALL(*component, manager()).WillOnce(Return(&myDummyComponentManager));
    gameObjectsManager.addGameObject(std::move(gameObject), dummyTag);
    Mock::AllowLeak(component);
    Mock::VerifyAndClearExpectations(component);

    ASSERT_TRUE(gameObjectsManager.hasComponentManager(&myDummyComponentManager));
    ASSERT_FALSE(gameObjectsManager.hasOutputComponentManager(
        static_cast<IOutputComponentManager *>(static_cast<IComponentManager *>(&myDummyComponentManager))));
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

TEST_F(TheGameObjectsManager, UsesTheComponentManagersToRegisterTheComponentsWhenYouAddANewGameObject)
{
    auto myDummyComponent{gameObject->addComponent<MyDummyComponent>()};
    myDummyComponent->setManager(&myMockComponentManager);
    EXPECT_CALL(myMockComponentManager, registerComponent(myDummyComponent));
    gameObjectsManager.addGameObject(std::move(gameObject), dummyTag);
}

TEST_F(TheGameObjectsManager, UsesTheComponentManagersToUpdateTheGameObjectComponents)
{
    auto myDummyComponent{gameObject->addComponent<MyDummyComponent>()};
    myDummyComponent->setManager(&myMockComponentManager);
    gameObjectsManager.addGameObject(std::move(gameObject), dummyTag);
    EXPECT_CALL(myMockComponentManager, updateComponents(dummyDeltaTime));
    gameObjectsManager.updateGameObjects(dummyDeltaTime);
}

TEST_F(TheGameObjectsManager, UsesTheComponentManagersToDestroyTheGameObjectComponents)
{
    auto myDummyComponent{gameObject->addComponent<MyDummyComponent>()};
    myDummyComponent->setManager(&myMockComponentManager);
    gameObjectsManager.addGameObject(std::move(gameObject), dummyTag);
    EXPECT_CALL(myMockComponentManager, destroyComponents());
    gameObjectsManager.destroyAllGameObjects();
}

TEST_F(TheGameObjectsManager, UsesTheOutputComponentManagersToGenerateOutput)
{
    auto myDummyComponent{gameObject->addComponent<MyDummyComponent>()};
    myDummyComponent->setManager(&myMockOutputComponentManager);
    gameObjectsManager.addGameObject(std::move(gameObject), dummyTag);
    EXPECT_CALL(myMockOutputComponentManager, output());
    gameObjectsManager.generateOutputFromGameObjects();
}
