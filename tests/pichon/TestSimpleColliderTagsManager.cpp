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

struct SimpleColliderTagsManagerTest : testing::Test
{
    SimpleColliderTagsManager tagsManager;
    const char *roleA{"RoleA"};
    const char *roleB{"RoleB"};
};

TEST_F(SimpleColliderTagsManagerTest, ConsidersATagAsBeingInvalidIfItContainsMoreThanTwoSeparators)
{
    ASSERT_FALSE(tagsManager.validTag("RoleA_Role_B"));
}

TEST_F(SimpleColliderTagsManagerTest, ConsidersATagAsBeingInvalidIfItIsEmpty)
{
    ASSERT_FALSE(tagsManager.validTag(""));
}

TEST_F(SimpleColliderTagsManagerTest, ConsidersATagAsBeingValidIfItIsOfTheForm_RoleA_Separator_RoleB)
{
    ASSERT_TRUE(tagsManager.validTag("RoleA_RoleB"));
}

TEST_F(SimpleColliderTagsManagerTest, ConsidersATagAsBeingInvalidIfItStartsOrEndsWithTheSeparator)
{
    ASSERT_FALSE(tagsManager.validTag("_RoleARoleB"));
    ASSERT_FALSE(tagsManager.validTag("RoleARoleB_"));
    ASSERT_FALSE(tagsManager.validTag("_RoleARole_B"));
}

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

TEST_F(SimpleColliderTagsManagerTest, GivesYouTheRolesFromAGivenTag)
{
    auto [role1, role2]{tagsManager.getRolesForTag("RoleA_RoleB")};
    ASSERT_TRUE(role1 != role2);
    ASSERT_TRUE(role1 == "RoleA" || role1 == "RoleB");
    ASSERT_TRUE(role2 == "RoleA" || role2 == "RoleB");
}

TEST_F(SimpleColliderTagsManagerTest, ThrowsIfGivenAnInvalidTagToGetTheRoles)
{
    ASSERT_THROW(tagsManager.getRolesForTag("RoleA_Role_B"), std::runtime_error);
}

TEST_F(SimpleColliderTagsManagerTest, ThrowsIfGivenAtLeastAnInvalidTagToCompareForEquality)
{
    ASSERT_THROW(tagsManager.tagsAreEqual("", "RoleA_RoleB"), std::runtime_error);
    ASSERT_THROW(tagsManager.tagsAreEqual("", ""), std::runtime_error);
}
