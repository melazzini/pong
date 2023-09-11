#include "MockColliderComponent.h"
#include "components/ColliderComponent.h"
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
    std::string otherRole1{"otherRole1"};
    std::string otherRole2{"otherRole2"};
    size_t nColisions1{1};
    size_t nColisions2{1};
    std::set<CollisionType> collisions;
    CollisionType collisionToBeInserted{otherRole1, nColisions1};
    DummyColliderDescriptor colliderDescriptor1{std::make_unique<DummyColliderShape>(), role};
    DummyColliderDescriptor colliderDescriptor2{std::make_unique<DummyColliderShape>(), role};
    ColliderComponentWithDummyShape collider1{std::move(colliderDescriptor1), &gameObject, &manager};
    ColliderComponentWithDummyShape collider2{std::move(colliderDescriptor2), &gameObject, &manager};
    size_t dummyNumberOfCollisions{20};
    void SetUp() override
    {
        collisions.emplace(collisionToBeInserted);
    }
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
    DummyColliderDescriptor colliderDescriptor_{std::make_unique<DummyColliderShape>(), role};
    ColliderComponentWithDummyShape collider_{std::move(colliderDescriptor_), &gameObject, &manager};
    ASSERT_THAT(collider_.role(), Eq(role));
}

TEST_F(AColliderComponent, HasItsCollisionsList)
{
    DummyColliderDescriptor colliderDescriptor_{std::make_unique<DummyColliderShape>(), role, collisions};
    ColliderComponentWithDummyShape collider_{std::move(colliderDescriptor_), &gameObject, &manager};
    ASSERT_TRUE(collisions == collider_.collisions());
}

TEST_F(AColliderComponent, CanDetermineItsMaxNumberOfCollisionsItCanWantsToHandleAtOnce)
{
    ASSERT_THAT(collider1.maxNumberOfCollisions(), Ne(dummyNumberOfCollisions));
    collider1.setMaxNumberOfCollisions(dummyNumberOfCollisions);
    ASSERT_THAT(collider1.maxNumberOfCollisions(), Eq(dummyNumberOfCollisions));
}
