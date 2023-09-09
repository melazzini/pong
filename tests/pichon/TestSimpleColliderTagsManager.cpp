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
