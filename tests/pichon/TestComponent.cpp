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

struct AComponent : testing::Test
{
    DummyComponentManager componentManager;
    DummyGameObject gameObject;
};

TEST_F(AComponent, NeedsItsGameObjectAndComponentManagerInOrderToBeInitialized)
{
    Component component{&gameObject, &componentManager};
}

TEST_F(AComponent, ThrowsIfGivenANullGameObject)
{
    ASSERT_THROW(Component(nullptr, &componentManager), std::runtime_error);
}

TEST_F(AComponent, ThrowsIfGivenANullComponentManager)
{
    ASSERT_THROW(Component(&gameObject, nullptr), std::runtime_error);
}

TEST_F(AComponent, RemembersItsManager)
{
    Component component{&gameObject, &componentManager};
    ASSERT_THAT(component.manager(), Eq(&componentManager));
}
