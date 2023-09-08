#include "MockColliderComponent.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

using testing::Eq;
using testing::Ne;
using testing::Return;

struct AColliderComponent : testing::Test
{
    MockColliderComponentManagerBase manager;
    GameObject gameObject;
    std::string role{"role"};
    ColliderComponentWithDummyShape collider1{role, std::make_unique<DummyColliderShape>(), &gameObject, &manager};
    ColliderComponentWithDummyShape collider2{role, std::make_unique<DummyColliderShape>(), &gameObject, &manager};
};

TEST_F(AColliderComponent, UsesItsShapeToDetermineWhetherThereIsACollision)
{
    collider1.shape()->collides = false;
    ASSERT_FALSE(collider1.collidesWith(collider2));
    collider1.shape()->collides = true;
    ASSERT_TRUE(collider1.collidesWith(collider2));
}

TEST_F(AColliderComponent, HasItsRole)
{
    ColliderComponentWithDummyShape collider_{role, std::make_unique<DummyColliderShape>(), &gameObject, &manager};
    ASSERT_THAT(collider_.role(), Eq(role));
}
