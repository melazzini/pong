#include "GameObject.h"
#include "MockColliderComponent.h"
#include "components/ColliderComponent.h"
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
using testing::Ge;
using testing::Mock;
using testing::Ne;
using testing::NiceMock;
using testing::Return;

TEST(ColliderComponentManagerBaseTest, RequiresAColliderTagsManagerAndTheCollisionContainer)
{
    ColliderComponentManagerWithDummyShape ccm{std::make_shared<MockColliderTagsManager>(),
                                               std::make_unique<MockCollisionContainerWithDummyShape>()};
}

struct AColliderComponentManager : testing::Test
{
    ColliderComponentManagerWithDummyShape *ccm;
    std::shared_ptr<NiceMock<MockColliderTagsManager>> tagsManager;
    MockCollisionContainerWithDummyShape *containerSpy;
    float dummyDeltatime{0};
    std::unordered_set<std::string> dummyTags;
    std::string dummyTag1{"RoleA_RoleB"};
    void SetUp() override
    {
        dummyTags.emplace(dummyTag1);
        tagsManager = std::make_shared<NiceMock<MockColliderTagsManager>>();
        auto container_{std::make_unique<NiceMock<MockCollisionContainerWithDummyShape>>()};
        containerSpy = container_.get();
        ccm = new ColliderComponentManagerWithDummyShape{tagsManager, std::move(container_)};
    }
    void TearDown() override
    {
        delete ccm;
        Mock::VerifyAndClearExpectations(containerSpy);
        Mock::AllowLeak(containerSpy);
    }
};

TEST_F(AColliderComponentManager, GetsAllTheTagsFromTheContainerWhenItUpdates)
{
    EXPECT_CALL(*containerSpy, getAllTags).WillOnce([this]() -> const std::unordered_set<std::string> & {
        return dummyTags;
    });
    ccm->update(dummyDeltatime);
}

struct AColliderComponentManagerExpectedToGetAllTagsUsingTheContainerWhenUpdates : AColliderComponentManager
{
    void SetUp() override
    {
        AColliderComponentManager::SetUp();
        EXPECT_CALL(*containerSpy, getAllTags).WillOnce([this]() -> const std::unordered_set<std::string> & {
            return dummyTags;
        });
    }
};

TEST_F(AColliderComponentManagerExpectedToGetAllTagsUsingTheContainerWhenUpdates,
       UsesTheColliderTagsManagerToGetTheRolesOfTheColliders)
{
    EXPECT_CALL(*tagsManager, getRolesForTag).WillOnce([]() -> std::pair<std::string, std::string> {
        return {"RoleA", "RoleB"};
    });
    ccm->update(dummyDeltatime);
}

struct AColliderComponentManagerWhichObtainedTheColliderRolesFromTheColliderTagsManager
    : AColliderComponentManagerExpectedToGetAllTagsUsingTheContainerWhenUpdates
{
    std::unordered_set<ColliderComponentWithDummyShape *> collidersA;
    std::unordered_set<ColliderComponentWithDummyShape *> collidersB;
    ColliderComponentWithDummyShape *colliderA1{};
    ColliderComponentWithDummyShape *colliderB1{};
    GameObject ownerA;
    GameObject ownerB;
    DummyColliderShape *shapeASpy{};
    void SetUp() override
    {
        AColliderComponentManagerExpectedToGetAllTagsUsingTheContainerWhenUpdates::SetUp();
        CollisionType collisionTypeA{.roleOfInterest = "RoleB", .maxNumberOfCollisions = 1};
        CollisionType collisionTypeB{.roleOfInterest = "RoleA", .maxNumberOfCollisions = 1};
        std::unique_ptr<DummyColliderShape> shapeA{std::make_unique<DummyColliderShape>()};
        shapeASpy = shapeA.get();
        DummyColliderDescriptor descriptorA{std::move(shapeA), "RoleA", {collisionTypeA}};
        DummyColliderDescriptor descriptorB{std::make_unique<DummyColliderShape>(), "RoleA", {collisionTypeB}};
        colliderA1 = new ColliderComponentWithDummyShape(std::move(descriptorA), &ownerA, ccm);
        colliderB1 = new ColliderComponentWithDummyShape(std::move(descriptorB), &ownerB, ccm);

        collidersA.emplace(colliderA1);
        collidersB.emplace(colliderB1);

        EXPECT_CALL(*tagsManager, getRolesForTag).WillOnce([]() -> std::pair<std::string, std::string> {
            return {"RoleA", "RoleB"};
        });
    }

    void TearDown() override
    {
        delete colliderA1;
        delete colliderB1;
        AColliderComponentManagerExpectedToGetAllTagsUsingTheContainerWhenUpdates::TearDown();
    }
};

TEST_F(AColliderComponentManagerWhichObtainedTheColliderRolesFromTheColliderTagsManager,
       GetAllTheColliderComponentsForTheGivenRolesFromTheContainer)
{
    EXPECT_CALL(*containerSpy, getCollidersByRole("RoleA"))
        .WillOnce(
            [this](const std::string &role) -> std::optional<std::unordered_set<ColliderComponentWithDummyShape *> *> {
                return &collidersA;
            });
    EXPECT_CALL(*containerSpy, getCollidersByRole("RoleB"))
        .WillOnce(
            [this](const std::string &role) -> std::optional<std::unordered_set<ColliderComponentWithDummyShape *> *> {
                return &collidersB;
            });
    ccm->update(dummyDeltatime);
}

// struct AColliderComponentManagerWhenDetectsACollision
//     : AColliderComponentManagerWhichObtainedTheColliderRolesFromTheColliderTagsManager
//{
// };
//
// TEST_F(AColliderComponentManagerWhenDetectsACollision, StoresTheCollisionForTheGivenColliders)
//{
//     FAIL();
// }

// TEST_F(AColliderComponentManager, HasASetOfCollisionTags)
//{
//     ccm.collisionTags();
// }
//
// TEST_F(AColliderComponentManager, GivesAnEmptySetOfTagsIfTheGivenColliderComponentHasntBeenAddedYet)
//{
//     ASSERT_TRUE(ccm.collisionTagsFor(colliderComponentNotInsertedYet).empty());
// }
//
// TEST_F(AColliderComponentManager,
//        GivesANumberOfTagsCorrespondingTo_ATLEAST_TheNumberOfCollisionsTheAddedColliderCaresAbout)
//{
//     auto numberOfCollisions{colliderComponent->collisions().size()};
//     ASSERT_THAT(numberOfCollisions, Eq(1));
//     ccm.registerComponent(colliderComponent.get());
//     ASSERT_THAT(ccm.collisionTagsFor(*colliderComponent).size(), Ge(numberOfCollisions));
// }

