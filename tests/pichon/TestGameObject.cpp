#include "GameObject.h"
#include "components.h"
#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using testing::DoubleEq;
using testing::Eq;
using testing::Mock;
using testing::Ne;

struct DummyComponentManger : ComponentManager
{
};

struct DummyComponent : Component
{
    DummyComponent(GameObject *owner, ComponentManager *componentManger) : Component(owner, componentManger)
    {
    }
    MOCK_METHOD(void, update, (uint32_t), (override));
};

TEST(AGameObject, CanAddAComponent)
{
    DummyComponentManger dummyManager;
    GameObject gameObject{};
    ASSERT_FALSE(gameObject.hasComponent<DummyComponent>());
    gameObject.addComponent<DummyComponent>(&gameObject, &dummyManager);
    ASSERT_TRUE(gameObject.hasComponent<DummyComponent>());
}

