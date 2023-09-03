#include "Component.h"
#include "DrawableComponent.h"
#include "GameObject.h"
#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using testing::Eq;
using testing::Ne;

struct DummyComponent : Component
{
    void update(float deltaTime) override
    {
    }
};

TEST(AGameObject, CanAddAComponent)
{
    GameObject gameObject{};
    ASSERT_FALSE(gameObject.hasComponent<DummyComponent>());
    gameObject.addComponent<DummyComponent>();
    ASSERT_TRUE(gameObject.hasComponent<DummyComponent>());
}

