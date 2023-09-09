#include "MockColliderComponent.h"
#include "components/BoxColliderComponent.h"
#include "components/ColliderComponent.h"
#include "utils.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <vector>

using testing::Eq;
using testing::Ge;
using testing::Ne;
using testing::Return;

struct AColliderComponentManager : testing::Test
{
    ColliderComponentManagerWithDummyShape ccm;
    GameObject gameObject;
    std::string role{"role"};
    std::string otherRole1{"otherRole1"};
    size_t nColisions1{1};
    std::set<CollisionType> collisions;
    CollisionType collisionToBeInserted{otherRole1, nColisions1};
    DummyColliderDescriptor colliderDescriptor1{std::make_unique<DummyColliderShape>(), role};
    ColliderComponentWithDummyShape colliderComponentNotInsertedYet{std::move(colliderDescriptor1), &gameObject, &ccm};
    std::unique_ptr<ColliderComponentWithDummyShape>
        colliderComponent; //{std::move(colliderDescriptor2), &gameObject, &ccm};
    void SetUp() override
    {
        collisions.emplace(collisionToBeInserted);
        DummyColliderDescriptor colliderDescriptor{std::make_unique<DummyColliderShape>(), role, collisions};
        colliderComponent =
            std::make_unique<ColliderComponentWithDummyShape>(std::move(colliderDescriptor), &gameObject, &ccm);
    }
};

TEST_F(AColliderComponentManager, HasASetOfCollisionTags)
{
    ccm.collisionTags();
}

TEST_F(AColliderComponentManager, GivesAnEmptySetOfTagsIfTheGivenColliderComponentHasntBeenAddedYet)
{
    ASSERT_TRUE(ccm.collisionTagsFor(colliderComponentNotInsertedYet).empty());
}

TEST_F(AColliderComponentManager,
       GivesANumberOfTagsCorrespondingTo_ATLEAST_TheNumberOfCollisionsTheAddedColliderCaresAbout)
{
    auto numberOfCollisions{colliderComponent->collisions().size()};
    ASSERT_THAT(numberOfCollisions, Eq(1));
    ccm.registerComponent(colliderComponent.get());
    ASSERT_THAT(ccm.collisionTagsFor(*colliderComponent).size(), Ge(numberOfCollisions));
}

// TODO: test drive this first!
struct IColliderTagsManager
{
    virtual std::string buildTag(const std::string &colliderRoleA, const std::string &colliderRoleB) const = 0;

    virtual bool tagsAreEqual(const std::string &tagA, const std::string &tagB) const = 0;
};

struct SimpleColliderTagsManager : IColliderTagsManager
{
    inline static const std::string SEPARATOR{"_"};
    std::string buildTag(const std::string &colliderRoleA, const std::string &colliderRoleB) const override
    {
        return colliderRoleA + SEPARATOR + colliderRoleB;
    }

    bool tagsAreEqual(const std::string &tagA, const std::string &tagB) const override
    {
        std::vector<std::string> rolesTagsA{splitByListOfCharSeparators(tagA, SEPARATOR)};
        std::vector<std::string> rolesTagsB{splitByListOfCharSeparators(tagB, SEPARATOR)};
        return (rolesTagsA[0] == rolesTagsB[0] && rolesTagsA[1] == rolesTagsB[1]) ||
               (rolesTagsA[0] == rolesTagsB[1] && rolesTagsA[1] == rolesTagsB[0]);
    }
};

struct SimpleColliderTagsManagerTest : testing::Test
{
    SimpleColliderTagsManager tagsManager;
    const char *roleA{"RoleA"};
    const char *roleB{"RoleB"};
};

TEST_F(SimpleColliderTagsManagerTest, BuildsTagsFromTwoRolesAsFollows_RoleLeft_SEPARATOR_RoleRight)
{
    auto tag{tagsManager.buildTag(roleA, roleB)};
    ASSERT_THAT(tag, Eq(roleA + SimpleColliderTagsManager::SEPARATOR + roleB));
}

TEST_F(SimpleColliderTagsManagerTest, ConsidersTag_RoleA_RoleB_EqualTo_RoleB_RoleA)
{
    ASSERT_TRUE(tagsManager.tagsAreEqual("RoleA_RoleB", "RoleB_RoleA"));
}

TEST_F(SimpleColliderTagsManagerTest, ConsidersTwoTagsAsDifferentIfTheRolesAreDifferent)
{
    ASSERT_FALSE(tagsManager.tagsAreEqual("RoleA_RoleC", "RoleB_RoleA"));
}
