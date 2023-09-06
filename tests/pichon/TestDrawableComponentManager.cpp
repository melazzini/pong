#include "GameObject.h"
#include "components/Component.h"
#include "components/DrawableComponent.h"
#include "components/TransformComponent.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using testing::Eq;
using testing::Ne;
using testing::Return;

TEST(TheDrawableComponentManager, IsASingleTon)
{
    DrawableComponentManager *instance1{DrawableComponentManager::getInstance()};
    DrawableComponentManager *instance2{DrawableComponentManager::getInstance()};
    ASSERT_THAT(instance1, Ne(nullptr));
    ASSERT_THAT(instance1, Eq(instance2));
}
