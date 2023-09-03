#include "Component.h"
#include "GameObject.h"
#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using testing::DoubleEq;
using testing::Eq;
using testing::Mock;
using testing::Ne;

struct DummyComponent : Component
{
    MOCK_METHOD(void, update, (float), (override));
};

TEST(AGameObject, CanAddAComponent)
{
    GameObject gameObject{};
    ASSERT_FALSE(gameObject.hasComponent<DummyComponent>());
    gameObject.addComponent<DummyComponent>();
    ASSERT_TRUE(gameObject.hasComponent<DummyComponent>());
}

TEST(AGameObject, UpdatesItsComponentsPassingThemTheDeltaTime)
{
    GameObject gameObject{};
    float dummyDeltatime{10.00};
    auto dummyComponent = gameObject.addComponent<DummyComponent>();
    EXPECT_CALL(*dummyComponent, update).WillOnce([dummyDeltatime](float deltatime) {
        ASSERT_DOUBLE_EQ(deltatime, dummyDeltatime);
    });
    gameObject.updateComponents(dummyDeltatime);
}
