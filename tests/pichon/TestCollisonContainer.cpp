#include "MockColliderComponent.h"
#include "components/CollisionContainer.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <utility>

using testing::AtLeast;
using testing::Eq;
using testing::Mock;
using testing::Ne;
using testing::Return;

using CollisionContainerWithDummyShape = CollisionContainer<DummyColliderShape>;

struct MockColliderTagsManager : IColliderTagsManager
{
    MOCK_METHOD(std::string, buildTag, (const std::string &, const std::string &), (const override));
    MOCK_METHOD(bool, tagsAreEqual, (const std::string &, const std::string &), (const override));
};

struct CollisionContainerTest : testing::Test
{
    MockColliderComponentManagerBase manager;
    GameObject gameObject;
    std::string role{"role"};
    std::string roleOfInterest{"otherRole1"};
    size_t nColisions{1};
    std::set<CollisionType> collisions{CollisionType{roleOfInterest, nColisions}};
    DummyColliderDescriptor colliderDescriptor{std::make_unique<DummyColliderShape>(), role};
    ColliderComponentWithDummyShape collider{std::move(colliderDescriptor), &gameObject, &manager};
    CollisionInfo<DummyColliderShape> info{role, &collider, roleOfInterest, nColisions};
    std::unique_ptr<MockColliderTagsManager> tagsManager{std::make_unique<MockColliderTagsManager>()};
    MockColliderTagsManager *tagsManagerSpy{tagsManager.get()};
    std::unique_ptr<CollisionContainerWithDummyShape> container; //{std::move(tagsManager)};
    std::string dummyTag{"DummyTag"};
    void SetUp() override
    {
        container = std::make_unique<CollisionContainerWithDummyShape>(std::move(tagsManager));
    }
    void TearDown() override
    {
        Mock::VerifyAndClearExpectations(tagsManagerSpy);
        Mock::AllowLeak(tagsManagerSpy);
    }
};

TEST_F(CollisionContainerTest, UsesItsTagsManagerToBuildATagWhenACollisionIsInserted)
{
    EXPECT_CALL(*tagsManagerSpy, buildTag).Times(AtLeast(1));
    container->insertCollision(info);
}

TEST_F(CollisionContainerTest, CanAddACollision)
{
    ASSERT_FALSE(container->hasCollision(info));
    container->insertCollision(info);
    ASSERT_TRUE(container->hasCollision(info));
}

TEST_F(CollisionContainerTest, ReturnsANonEmptyTagIfTheCollisionExist)
{
    EXPECT_CALL(*tagsManagerSpy, buildTag).WillRepeatedly(Return(dummyTag));
    container->insertCollision(info);
    ASSERT_TRUE(container->hasCollision(info));
    auto tagForCollision{container->tagForCollision(info)};
    ASSERT_FALSE(tagForCollision->empty());
}
TEST_F(CollisionContainerTest, DoesntReturnATagIfTheCollisionDoesntExist)
{
    EXPECT_CALL(*tagsManagerSpy, buildTag).WillRepeatedly(Return(dummyTag));
    ASSERT_FALSE(container->hasCollision(info));
    auto tagForCollision{container->tagForCollision(info)};
    ASSERT_FALSE(tagForCollision.has_value());
}
TEST_F(CollisionContainerTest, KnowsMaxNumberOfCollisionsForColliderAndItsCollisionTag)
{
    container->insertCollision(info);
    auto tagForCollision{container->tagForCollision(info)};
    auto maxNumberOfCollisions{container->maxNumberOfCollisions(tagForCollision.value(), info.colliderComponent)};
    ASSERT_THAT(maxNumberOfCollisions.value(), Eq(info.maxNumberOfCollisions));
}

TEST_F(CollisionContainerTest, RemembersInsertedCollidersByRole)
{
    container->insertCollision(info);
    auto colliderComponents{container->getCollidersByRole(info.colliderRole)};
    ASSERT_TRUE(colliderComponents.has_value());
    ASSERT_TRUE(colliderComponents.value() != nullptr);
    ASSERT_TRUE(colliderComponents.value()->contains(info.colliderComponent));
}
