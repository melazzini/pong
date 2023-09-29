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

struct TheGameLoop : testing::Test
{
    GameLoop gameLoop;
    MockComponentManager componentManager;
    MockOutputComponentManager outputComponentManager;
    std::vector<ComponentManager *> managers;
    std::vector<OutputComponentManager *> outputComponentManagers;
    uint32_t dummyDeltatime{0};
};

TEST_F(TheGameLoop, MakesTheComponentManagersUpdateWhenItIsOnUpdateStage)
{
    managers.push_back(&componentManager);
    EXPECT_CALL(componentManager, update(dummyDeltatime));
    gameLoop.update(dummyDeltatime, managers);
}

TEST_F(TheGameLoop, MakesTheOutputComponentManagersOutputContentWhenItIsOnOutputStage)
{
    outputComponentManagers.push_back(&outputComponentManager);
    EXPECT_CALL(outputComponentManager, output);
    gameLoop.output(outputComponentManagers);
}

TEST_F(TheGameLoop, MakesTheComponentManagersDestroyWhenItIsOnDestroyStage)
{
    managers.push_back(&componentManager);
    EXPECT_CALL(componentManager, destroy);
    gameLoop.destroy(managers);
}
