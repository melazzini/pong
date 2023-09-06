#include "components/InputComponent.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using testing::Eq;
using testing::Ne;
using testing::Return;

TEST(TheInputComponentManager, IsASingleTon)
{
    InputComponentManager *instance1{InputComponentManager::getInstance()};
    InputComponentManager *instance2{InputComponentManager::getInstance()};
    ASSERT_THAT(instance1, Ne(nullptr));
    ASSERT_THAT(instance1, Eq(instance2));
}
