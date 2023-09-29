#include "GameInterfaces.h"
#include "GameLoop.h"
#include "components/Component.h"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct MockComponentManager : ComponentManager
{
    MOCK_METHOD(void, update, (uint32_t), (override));
    MOCK_METHOD(void, destroy, (), (override));
};

struct MockOutputComponentManager : OutputComponentManager
{
    MOCK_METHOD(void, output, (), (override));
};

struct MockGameObjectsManager : IGameObjectsManager
{
    MOCK_METHOD(void, updateGameObjects, (uint32_t), (override));
    MOCK_METHOD(void, generateOutputFromGameObjects, (), (override));
    MOCK_METHOD(void, destroyAllGameObjects, (), (override));

    bool addGameObject(std::unique_ptr<GameObject>, const std::string &) override
    {
        return false;
    }

    bool removeGameObject(const std::string &) override
    {
        return false;
    }

    bool hasGameObject(const std::string &) const override
    {
        return false;
    }

    bool hasComponentManager(ComponentManager *) const override
    {
        return false;
    }
};

struct TheGameLoop : testing::Test
{
    GameLoop gameLoop;
    MockGameObjectsManager gameObjectsManager;
    std::vector<OutputComponentManager *> outputComponentManagers;
    uint32_t dummyDeltatime{0};
};

TEST_F(TheGameLoop, UpdatesTheGameObjectsUsingTheGameObjectsManager)
{
    EXPECT_CALL(gameObjectsManager, updateGameObjects(dummyDeltatime));
    gameLoop.update(dummyDeltatime, &gameObjectsManager);
}

TEST_F(TheGameLoop, GeneratesOuputUsingTheGameObjectsManager)
{
    EXPECT_CALL(gameObjectsManager, generateOutputFromGameObjects);
    gameLoop.generateOutput(&gameObjectsManager);
}

TEST_F(TheGameLoop, DestroysTheGameObjectsUsingTheGameObjectsManager)
{
    EXPECT_CALL(gameObjectsManager, destroyAllGameObjects);
    gameLoop.destroy(&gameObjectsManager);
}
