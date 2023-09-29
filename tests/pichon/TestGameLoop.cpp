#include "GameLoop.h"
#include "components/Component.h"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct MockComponentManager : ComponentManager
{
    MOCK_METHOD(void, update, (uint32_t), (override));
};

struct TheGameLoop : testing::Test
{
    GameLoop gameLoop;
    MockComponentManager componentManager;
    MockComponentManager anotherComponentManager;
    std::vector<ComponentManager *> managers;
    uint32_t dummyDeltatime{0};
};

TEST_F(TheGameLoop, MakesTheComponentManagersUpdateWhenItUpdates)
{
    managers.push_back(&componentManager);
    EXPECT_CALL(componentManager, update(dummyDeltatime));
    gameLoop.update(dummyDeltatime, managers);
}
