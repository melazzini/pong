#include "MockColliderComponent.h"
#include "components/CollisionContainer.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <utility>

using testing::AtLeast;
using testing::Eq;
using testing::Mock;
using testing::Ne;
using testing::Return;

using CollisionContainerWithDummyShape = CollisionContainer<DummyColliderShape>;

struct CollisionContainerTest : testing::Test
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
    ColliderComponentWithDummyShape colliderOtherRole{std::move(colliderDescriptorOtherRole), &gameObjectOtherRole,
                                                      &manager};
    CollisionInfo<DummyColliderShape> info{role, &collider, roleOfInterest};
    std::shared_ptr<MockColliderTagsManager> tagsManager{std::make_shared<MockColliderTagsManager>()};
    MockColliderTagsManager *tagsManagerSpy{tagsManager.get()};
    std::unique_ptr<CollisionContainerWithDummyShape> container; //{std::move(tagsManager)};
    std::string dummyTag{"DummyTag"};
    std::string emptyTag{""};
    void SetUp() override
    {
        container = std::make_unique<CollisionContainerWithDummyShape>(tagsManager);
    }
    void TearDown() override
    {
        Mock::VerifyAndClearExpectations(tagsManagerSpy);
        Mock::AllowLeak(tagsManagerSpy);
    }
};

struct CollisionContainerTestWithMockTagsManagerConfiguredToReturnDummyTag : CollisionContainerTest
{
    void SetUp() override
    {
        CollisionContainerTest::SetUp();
        EXPECT_CALL(*tagsManagerSpy, buildTag).WillRepeatedly(Return(dummyTag));
    }
};

TEST_F(CollisionContainerTest, UsesItsTagsManagerToBuildATagWhenACollisionIsInserted)
{
    EXPECT_CALL(*tagsManagerSpy, buildTag).WillRepeatedly(Return(dummyTag));
    container->insertCollisionInfo(info);
}

TEST_F(CollisionContainerTest, ThrowsIfTheTagsManagerBuildEmpyTag)
{
    EXPECT_CALL(*tagsManagerSpy, buildTag).WillRepeatedly(Return(emptyTag));
    ASSERT_THROW(container->insertCollisionInfo(info), std::runtime_error);
}

TEST_F(CollisionContainerTest, CanInsertACollisionInfo)
{
    EXPECT_CALL(*tagsManagerSpy, buildTag).WillRepeatedly(Return(dummyTag));
    ASSERT_FALSE(container->hasCollision(info));
    container->insertCollisionInfo(info);
    ASSERT_TRUE(container->hasCollision(info));
}

TEST_F(CollisionContainerTest, CanRecordAnOccurredCollision)
{
    ASSERT_FALSE(container->colliderHasRecordOfCollisions(&collider));
    container->recordCollision(&collider, OccurredCollisionInfoWithDummyShape{otherRole, &colliderOtherRole});
    ASSERT_TRUE(container->colliderHasRecordOfCollisions(&collider));
}

TEST_F(CollisionContainerTestWithMockTagsManagerConfiguredToReturnDummyTag, ReturnsANonEmptyTagIfTheCollisionExist)
{
    container->insertCollisionInfo(info);
    ASSERT_TRUE(container->hasCollision(info));
    auto tagForCollision{container->tagForCollision(info)};
    ASSERT_FALSE(tagForCollision->empty());
}
TEST_F(CollisionContainerTestWithMockTagsManagerConfiguredToReturnDummyTag, DoesntReturnATagIfTheCollisionDoesntExist)
{
    ASSERT_FALSE(container->hasCollision(info));
    auto tagForCollision{container->tagForCollision(info)};
    ASSERT_FALSE(tagForCollision.has_value());
}

TEST_F(CollisionContainerTestWithMockTagsManagerConfiguredToReturnDummyTag,
       KnowsCurrentNumberOfRecordedCollisionsForACollider)
{
    ASSERT_FALSE(container->numberOfRecordedCollisionsForCollider(&collider).has_value());
    container->recordCollision(&collider, OccurredCollisionInfoWithDummyShape{otherRole, &colliderOtherRole});
    ASSERT_THAT(container->numberOfRecordedCollisionsForCollider(&collider), Eq(1));
}

TEST_F(CollisionContainerTestWithMockTagsManagerConfiguredToReturnDummyTag, RemembersInsertedCollidersByRole)
{
    container->insertCollisionInfo(info);
    auto colliderComponents{container->getCollidersByRole(info.colliderRole)};
    ASSERT_TRUE(colliderComponents.has_value());
    ASSERT_TRUE(colliderComponents.value() != nullptr);
    ASSERT_TRUE(colliderComponents.value()->contains(info.colliderComponent));
}

TEST_F(CollisionContainerTestWithMockTagsManagerConfiguredToReturnDummyTag, ReturnsASetOfAllTheTagsItHas)
{
    container->insertCollisionInfo(info);
    ASSERT_FALSE(container->getAllTags().empty());
}
