#include "GameObject.h"
#include "components/Component.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using testing::Eq;
using testing::Return;

struct DummyGameObject : GameObject
{
};

struct DummyComponentManager : ComponentManager
{
};

TEST(AComponent, NeedsItsGameObjectAndComponentManagerInOrderToBeInitialized)
{
    DummyComponentManager componentManager;
    DummyGameObject gameObject;
    Component component{&gameObject, &componentManager};
}

TEST(AComponent, ThrowsIfGivenANullGameObject)
{
    DummyComponentManager componentManager;
    ASSERT_THROW(Component(nullptr, &componentManager), std::runtime_error);
}

TEST(AComponent, ThrowsIfGivenANullComponentManager)
{
    DummyGameObject gameObject;
    ASSERT_THROW(Component(&gameObject, nullptr), std::runtime_error);
}

TEST(AComponent, RemembersItsManager)
{
    DummyComponentManager componentManager;
    DummyGameObject gameObject;
    Component component{&gameObject, &componentManager};

    ASSERT_THAT(component.manager(), Eq(&componentManager));
}
