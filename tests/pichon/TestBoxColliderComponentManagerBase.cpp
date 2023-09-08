#include "EventManagementInterface.h"
#include "EventManager.h"
#include "EventUtils.h"
#include "GameObject.h"
#include "MockEventManager.h"
#include "components/BoxColliderComponent.h"
#include "components/InputComponent.h"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using testing::Eq;
using testing::Ne;
using testing::Return;

struct ABoxColliderComponentManagerBase : testing::Test
{
    GameObject gameObject1;
    GameObject gameObject2;
    std::string tag1 = "gameObject1";
    std::string tag2 = "gameObject2";
};

TEST_F(ABoxColliderComponentManagerBase, DISABLED_GivesTheTagsOfAllCollidersThatCollideWithAGivenCollider)
{
    BoxColliderComponentManagerBase boxColliderManager;
    BoxColliderComponent box1{&gameObject1, &boxColliderManager};
    BoxColliderComponent box2{&gameObject1, &boxColliderManager};
    boxColliderManager.checkForCollisionsWith(tag1);
}
