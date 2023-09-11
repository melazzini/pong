#pragma once

#include "GameObject.h"
#include "components/ColliderComponentManagerBase.h"
#include "components/CollisionContainer.h"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
struct DummyColliderShape
{
    bool collidesWith(const DummyColliderShape &other) const
    {
        return collides;
    }

    bool collides;
};

using ColliderComponentWithDummyShape = ColliderComponent<DummyColliderShape>;
using ColliderComponentManagerWithDummyShape = ColliderComponentManagerBase<DummyColliderShape>;
using DummyColliderDescriptor = ColliderDescriptor<DummyColliderShape>;
using ICollisionContainerWithDummyShape = ICollisionContainer<DummyColliderShape>;
using CollisionInfoWithDummyShape = CollisionInfo<DummyColliderShape>;
using OccurredCollisionInfoWithDummyShape = OccurredCollisionInfo<DummyColliderShape>;

struct MockCollisionContainerWithDummyShape : ICollisionContainerWithDummyShape
{
    MOCK_METHOD(void, insertCollisionInfo, (CollisionInfoWithDummyShape), (override));
    MOCK_METHOD(void, recordCollision, (ColliderComponentWithDummyShape *, OccurredCollisionInfoWithDummyShape),
                (override));
    MOCK_METHOD(std::optional<size_t>, numberOfRecordedCollisionsForCollider, (ColliderComponentWithDummyShape *),
                (const override));
    MOCK_METHOD(bool, hasCollision, (const CollisionInfoWithDummyShape &), (const override));
    MOCK_METHOD(bool, colliderHasRecordOfCollisions, (ColliderComponentWithDummyShape *), (const override));
    MOCK_METHOD(std::optional<std::string>, tagForCollision, (const CollisionInfoWithDummyShape &), (const override));
    MOCK_METHOD((std::optional<std::unordered_set<ColliderComponentWithDummyShape *> *>), getCollidersByRole,
                (const std::string &), (override));
    MOCK_METHOD(const std::unordered_set<std::string> &, getAllTags, (), (const override));
};

struct MockColliderTagsManager : IColliderTagsManager
{
    MOCK_METHOD(std::string, buildTag, (const std::string &, const std::string &), (const override));
    MOCK_METHOD(bool, tagsAreEqual, (const std::string &, const std::string &), (const override));
    MOCK_METHOD((std::pair<std::string, std::string>), getRolesForTag, (const std::string &), (const override));
    MOCK_METHOD(bool, validTag, (const std::string &), (const override));
};

struct MockColliderComponentManagerBase : ColliderComponentManagerWithDummyShape
{
    MockColliderComponentManagerBase()
        : ColliderComponentManagerWithDummyShape{std::make_shared<MockColliderTagsManager>(),
                                                 std::make_unique<MockCollisionContainerWithDummyShape>()}
    {
    }
};
