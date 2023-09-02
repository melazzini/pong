#include "Game.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Eq;
using testing::Ne;

TEST(TheGame, KnowsIfItsRunning)
{
    Game game;
    game.setRunning(true);
    ASSERT_TRUE(game.isRunning());
}
