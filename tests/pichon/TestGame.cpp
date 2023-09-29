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
using testing::Mock;
using testing::Ne;
using testing::NiceMock;

Game::GameBackend backend_;
TEST(AGame, IsASingleton)
{
    Game *game1 = Game::getInstance(&backend_);
    Game *game2 = Game::getInstance(&backend_);
    ASSERT_TRUE(game1 != nullptr);
    ASSERT_THAT(game1, Eq(game2));
}

TEST(TheGetInstanceFunction, ReturnsNullIfYouPassItANullGameBackend)
{
    Game *game = Game::getInstance(nullptr);
    ASSERT_TRUE(game == nullptr);
}

struct ADummyComponentManager : ComponentManager
{
    MOCK_METHOD(void, registerComponent, (IComponent *), (override));
};

struct TheGame : testing::Test
{
    Game *game{};
    void SetUp() override
    {
        game = Game::getInstance(&backend_);
    }
    void TearDown() override
    {
    }
};

TEST_F(TheGame, CanChangeItsWindowSize)
{
    ASSERT_THAT(game->windowSize(), Ne(RectangularGeometry{200, 200}));
    game->setWindowSize(RectangularGeometry{200, 200});
    ASSERT_THAT(game->windowSize(), Eq(RectangularGeometry{200, 200}));
}

