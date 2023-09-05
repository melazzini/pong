#include "Game.h"
#include "GameObject.h"
#include "RectangularGeometry.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Eq;
using testing::Ne;

TEST(AGame, IsASingleton)
{
    Game *game1 = Game::getInstance();
    Game *game2 = Game::getInstance();
    ASSERT_TRUE(game1 != nullptr);
    ASSERT_THAT(game1, Eq(game2));
}

struct TheGame : testing::Test
{
    Game *game{};
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

struct DummyGameObject : GameObject
{
};

TEST_F(TheGame, CanAddGameObjects)
{
    ASSERT_FALSE(game->hasGameObject("dummyGameObject"));
    game->addGameObject(std::make_unique<DummyGameObject>(), "dummyGameObject");
    ASSERT_TRUE(game->hasGameObject("dummyGameObject"));
}

TEST_F(TheGame, ReturnsFalseIfYouPassItANullGameObject)
{
    ASSERT_FALSE(game->addGameObject(nullptr, "dummy-dummyGameObject"));
}
TEST_F(TheGame, ReturnsFalseIfYouPassItADuplicatedTag)
{
    game->addGameObject(std::make_unique<DummyGameObject>(), "dummyGameObject");
    ASSERT_FALSE(game->addGameObject(std::make_unique<DummyGameObject>(), "dummyGameObject"));
}

TEST_F(TheGame, DoesntStoreTheGameObjectIfItReturnsFalse)
{
    ASSERT_FALSE(game->addGameObject(nullptr, "dummy-dummy"));
    ASSERT_FALSE(game->hasGameObject("dummy-dummy"));
}
