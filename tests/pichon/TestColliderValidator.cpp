#include "GameObject.h"
#include "MockColliderComponent.h"
#include "components/ColliderComponent.h"
#include "components/ColliderValidator.h"
#include "utils.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <optional>
#include <stdexcept>
#include <unordered_set>
#include <vector>

using testing::AtLeast;
using testing::Eq;
using testing::Mock;
using testing::Return;

using ColliderValidatorWithDummyShape = ColliderValidator<DummyColliderShape>;
using CollisionContainerWithDummyShape = CollisionContainer<DummyColliderShape>;

struct ColliderValidatorTest : testing::Test
{
    MockColliderComponentManagerBase manager;
    GameObject gameObject;
    GameObject gameObjectOtherRole;
    std::string role{"player"};
    std::string roleOfInterest{"enemy"};
    std::string otherRole{roleOfInterest};
    size_t nColisions{1};
    size_t nColisionsForOtherRole{1};
    std::set<CollisionType> collisions{CollisionType{roleOfInterest, nColisions}};
    DummyColliderDescriptor colliderDescriptor{std::make_unique<DummyColliderShape>(), role};
    DummyColliderDescriptor colliderDescriptorOtherRole{std::make_unique<DummyColliderShape>(), otherRole};
    ColliderComponentWithDummyShape collider{std::move(colliderDescriptor), &gameObject, &manager};
};

TEST_F(ColliderValidatorTest, AssertThatAColliderIsValidIfTheMaxNumberOfCollisionsOfItIsZero)
{
    ColliderValidatorWithDummyShape validator;
    collider.setMaxNumberOfCollisions(0);
    MockCollisionContainerWithDummyShape container;
    ASSERT_TRUE(validator.canColliderAcceptMoreCollisions(&container, &collider));
}

TEST_F(ColliderValidatorTest, AColliderIsInterestedInRecordingCollisionsIfItsMaxNumberOfCollisionsIsGreaterThanZero)
{
    ColliderValidatorWithDummyShape validator;
    collider.setMaxNumberOfCollisions(1);
    ASSERT_TRUE(validator.colliderIsInterestedInRecordingCollisions(&collider));
}

TEST_F(ColliderValidatorTest, AColliderIsNotInterestedInRecordingCollisionsIfItsMaxNumberOfCollisionsIsZero)
{
    ColliderValidatorWithDummyShape validator;
    collider.setMaxNumberOfCollisions(0);
    ASSERT_FALSE(validator.colliderIsInterestedInRecordingCollisions(&collider));
}

TEST_F(ColliderValidatorTest,
       AssertThatAColliderIsValidIfTheNumberOfRecordedCollisionsIsLessThanTheMaximumWhichIsGreatedThanZero)
{
    ColliderValidatorWithDummyShape validator;
    collider.setMaxNumberOfCollisions(2);
    MockCollisionContainerWithDummyShape container;
    EXPECT_CALL(container, numberOfRecordedCollisionsForCollider(&collider))
        .WillRepeatedly([](ColliderComponentWithDummyShape *) -> std::optional<size_t> { return 0; });
    ASSERT_TRUE(validator.canColliderAcceptMoreCollisions(&container, &collider));
}

TEST_F(ColliderValidatorTest, AssertsThatAColliderIsInvalidIfThereAreNoRecordsOfCollisionsForItInTheContainer)
{
    ColliderValidatorWithDummyShape validator;
    collider.setMaxNumberOfCollisions(1);
    MockCollisionContainerWithDummyShape container;
    EXPECT_CALL(container, numberOfRecordedCollisionsForCollider(&collider))
        .WillRepeatedly([](ColliderComponentWithDummyShape *) -> std::optional<size_t> { return std::nullopt; });
    ASSERT_FALSE(validator.canColliderAcceptMoreCollisions(&container, &collider));
}
