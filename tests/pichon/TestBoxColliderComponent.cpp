#include "components/BoxColliderComponent.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using testing::Eq;
using testing::Ne;
using testing::Return;

TEST(TheBoxColliderComponentManager, IsASingleTon)
{
    BoxColliderComponentManager *instance1{BoxColliderComponentManager::getInstance()};
    BoxColliderComponentManager *instance2{BoxColliderComponentManager::getInstance()};
    ASSERT_THAT(instance1, Ne(nullptr));
    ASSERT_THAT(instance1, Eq(instance2));
}
