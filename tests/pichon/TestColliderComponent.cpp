#include "GameObject.h"
#include "components/ColliderComponent.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

using testing::Eq;
using testing::Ne;
using testing::Return;

struct DummyColliderShape
{
    bool collidesWith(const DummyColliderShape &other) const
    {
        return collides;
    }

    bool collides;
};

using ColliderComponentWithDummyShape = ColliderComponent<DummyColliderShape>;
using ColliderComponentManagerWithDummyShape = ColliderComponentManagerBase<DummyColliderShape>;

struct MockColliderComponentManagerBase : ColliderComponentManagerWithDummyShape
{
};

struct AColliderComponent : testing::Test
{
    MockColliderComponentManagerBase manager;
    GameObject gameObject;
    ColliderComponentWithDummyShape collider1{std::make_unique<DummyColliderShape>(), &gameObject, &manager};
    ColliderComponentWithDummyShape collider2{std::make_unique<DummyColliderShape>(), &gameObject, &manager};
};

TEST_F(AColliderComponent, UsesItsShapeToDetermineWhetherThereIsACollision)
{
    collider1.shape()->collides = false;
    ASSERT_FALSE(collider1.collidesWith(collider2));
    collider1.shape()->collides = true;
    ASSERT_TRUE(collider1.collidesWith(collider2));
}
