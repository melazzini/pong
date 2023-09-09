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
