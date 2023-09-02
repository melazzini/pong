#include "Game.h"
#include "RectangularGeometry.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Eq;
using testing::Ne;

TEST(TheGame, KnowsIfItsRunning)
{
    Game game{};
    game.setRunning(true);
    ASSERT_TRUE(game.isRunning());
}

TEST(TheGame, CanChangeItsWindowSize)
{
    Game game{};
    ASSERT_THAT(game.windowSize(), Ne(RectangularGeometry{200, 200}));
    game.setWindowSize(RectangularGeometry{200, 200});
    ASSERT_THAT(game.windowSize(), Eq(RectangularGeometry{200, 200}));
}

TEST(TheGame, RemembersItsInitialWindowSize)
{
    Game game{RectangularGeometry{600, 400}};
    ASSERT_THAT(game.windowSize(), Eq(RectangularGeometry{600, 400}));
}

TEST(TheGame, InitiallyIsNotRunning)
{
    Game game{};
    ASSERT_FALSE(game.isRunning());
}

TEST(TheGame, ByDefaultStartsWithTheWindowSizeGivenInTheGameConfigurationsFileAs_WINDOW_SIZE)
{
    Game game{};
    ASSERT_THAT(game.windowSize(), Eq(WINDOW_SIZE));
}
