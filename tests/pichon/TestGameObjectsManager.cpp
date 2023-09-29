#include "GameObject.h"
#include "GameObjectsManager.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct TheGameObjectsManager : testing::Test
{
    GameObjectsManager gameObjectsManager;
    GameObject go;
    const std::string dummyTag{"DummyTag"};
    const std::string existingGameObjectDummyTag{"ExistingGameObjectDummyTag"};

    void SetUp() override
    {
        gameObjectsManager.addGameObject(std::make_unique<GameObject>(), existingGameObjectDummyTag);
    }
};

TEST_F(TheGameObjectsManager, CanAddGameObjects)
{
    ASSERT_FALSE(gameObjectsManager.hasGameObject(dummyTag));
    gameObjectsManager.addGameObject(std::make_unique<GameObject>(), dummyTag);
    ASSERT_TRUE(gameObjectsManager.hasGameObject(dummyTag));
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
