#include "MockRenderer.h"
#include "components/DrawableComponent.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using testing::Eq;
using testing::Ne;
using testing::Return;

TEST(TheDrawableComponentManager, IsASingleTon)
{
    MockRenderer mockRenderer;
    DrawableComponentManager *instance1{DrawableComponentManager::getInstance(&mockRenderer)};
    DrawableComponentManager *instance2{DrawableComponentManager::getInstance(&mockRenderer)};
    ASSERT_THAT(instance1, Ne(nullptr));
    ASSERT_THAT(instance1, Eq(instance2));
}
