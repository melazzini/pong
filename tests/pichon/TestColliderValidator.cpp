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

TEST(ColliderValidatorTest, DISABLED_AssertThatAColliderIsValidIfTheMaxNumberOfCollisionsOfItIsZero)
{
    // ColliderValidator validator;
    // validator.isColliderAvailable(collider)
}
