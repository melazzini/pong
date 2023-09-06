#include "GameObject.h"
#include "components/Component.h"
#include "components/TransformComponent.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using testing::Eq;
using testing::Ne;
using testing::Return;

TEST(TheTransformComponentManager, IsASingleTon)
{
    TransformComponentManager *instance1{TransformComponentManager::getInstance()};
    TransformComponentManager *instance2{TransformComponentManager::getInstance()};
    ASSERT_THAT(instance1, Ne(nullptr));
}
