#include "Game.h"
#include "GameObject.h"
#include "components/Component.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using testing::Eq;
using testing::Return;

struct MockComponent : Component
{
    MockComponent(GameObject *owner, ComponentManager *manager) : Component(owner, manager)
    {
    }

    MOCK_METHOD(void, update, (float), (override));

    bool badComponent{};
};

struct ADummyGameObject : GameObject
{
};

TEST(AComponentManager, UpdatesAllItsComponentsWhenYouUpdateIt)
{
    ComponentManager manager;
    ADummyGameObject gameObject;
    MockComponent dummyComponent{&gameObject, &manager};
    manager.registerComponent(&dummyComponent);
    EXPECT_CALL(dummyComponent, update);
    manager.update(0);
}

TEST(AComponentManager, CanBeSetupToRefuseRegisteringCertainComponents)
{
    ComponentManager manager{[](Component *component) {
        if (static_cast<MockComponent *>(component)->badComponent)
        {
            return false;
        }
        return true;
    }};
    ADummyGameObject gameObject;
    MockComponent dummyComponent{&gameObject, &manager};
    dummyComponent.badComponent = true;
    ASSERT_FALSE(manager.hasComponent(&dummyComponent));
    manager.registerComponent(&dummyComponent);
    ASSERT_FALSE(manager.hasComponent(&dummyComponent));
    dummyComponent.badComponent = false;
    manager.registerComponent(&dummyComponent);
    ASSERT_TRUE(manager.hasComponent(&dummyComponent));
}

