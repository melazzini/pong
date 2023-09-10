#include "MockColliderComponent.h"
#include "components/BoxColliderComponent.h"
#include "components/ColliderComponent.h"
#include "utils.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <optional>
#include <stdexcept>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using testing::AtLeast;
using testing::Eq;
using testing::Mock;
using testing::Return;
// A hash function used to hash a pair of any kind
struct hash_pair
{
    template <class T1, class T2> size_t operator()(const std::pair<T1, T2> &p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);

        if (hash1 != hash2)
        {
            return hash1 ^ hash2;
        }

        // If hash1 == hash2, their XOR is zero.
        return hash1;
    }
};

template <typename TColliderShape> struct CollisionInfo
{
    std::string colliderRole{};
    ColliderComponent<TColliderShape> *colliderComponent{};
    std::string roleOfInterest{};
    size_t maxNumberOfCollisions{};
};

template <typename TColliderShape> struct ICollisionContainer
{
    virtual void insertCollision(CollisionInfo<TColliderShape> collisionInfo) = 0;
    virtual bool hasCollision(const CollisionInfo<TColliderShape> &collisionInfo) = 0;
    virtual std::optional<std::string> tagForCollision(const CollisionInfo<TColliderShape> &collisionInfo) = 0;
    virtual std::optional<size_t> maxNumberOfCollisions(const std::string &colliderTag,
                                                        ColliderComponent<TColliderShape> *collider) const = 0;
};

template <typename TColliderShape> class CollisionContainer : public ICollisionContainer<TColliderShape>
{
  public:
    CollisionContainer(std::unique_ptr<IColliderTagsManager> tagsManager)
        : m_colliderTagsManager{std::move(tagsManager)}
    {
    }
    void insertCollision(CollisionInfo<TColliderShape> collisionInfo) override
    {
        auto possibleTag1{m_colliderTagsManager->buildTag(collisionInfo.colliderRole, collisionInfo.roleOfInterest)};
        auto possibleTag2{m_colliderTagsManager->buildTag(collisionInfo.roleOfInterest, collisionInfo.colliderRole)};
        if (!m_tags.contains(possibleTag1) && !m_tags.contains(possibleTag2))
        {
            m_tags.emplace(possibleTag1);
            m_maxNumberOfCollisions[std::pair{possibleTag1, collisionInfo.colliderComponent}] =
                collisionInfo.maxNumberOfCollisions;
        }
    }

    bool hasCollision(const CollisionInfo<TColliderShape> &collisionInfo) override
    {
        auto possibleTag1{m_colliderTagsManager->buildTag(collisionInfo.colliderRole, collisionInfo.roleOfInterest)};
        auto possibleTag2{m_colliderTagsManager->buildTag(collisionInfo.roleOfInterest, collisionInfo.colliderRole)};
        if (!m_tags.contains(possibleTag1) && !m_tags.contains(possibleTag2))
        {
            return false;
        }
        return true;
    }

    std::optional<std::string> tagForCollision(const CollisionInfo<TColliderShape> &collisionInfo) override
    {
        auto possibleTag1{m_colliderTagsManager->buildTag(collisionInfo.colliderRole, collisionInfo.roleOfInterest)};
        auto possibleTag2{m_colliderTagsManager->buildTag(collisionInfo.roleOfInterest, collisionInfo.colliderRole)};
        if (!m_tags.contains(possibleTag1) && !m_tags.contains(possibleTag2))
        {
            return std::nullopt;
        }
        return possibleTag1;
    }

    std::optional<size_t> maxNumberOfCollisions(const std::string &colliderTag,
                                                ColliderComponent<TColliderShape> *collider) const override
    {
        if (m_maxNumberOfCollisions.contains({colliderTag, collider}))
        {
            return m_maxNumberOfCollisions.at({colliderTag, collider});
        }
        return std::nullopt;
    }

  private:
    std::unique_ptr<IColliderTagsManager> m_colliderTagsManager;
    std::unordered_set<std::string> m_tags;
    std::unordered_map<std::string, std::list<ColliderComponent<TColliderShape> *>> m_collidersByRole;
    std::unordered_map<std::pair<std::string, ColliderComponent<TColliderShape> *>, size_t, hash_pair>
        m_maxNumberOfCollisions;
};

using CollisionContainerWithDummyShape = CollisionContainer<DummyColliderShape>;

struct MockColliderTagsManager : IColliderTagsManager
{
    MOCK_METHOD(std::string, buildTag, (const std::string &, const std::string &), (const override));
    MOCK_METHOD(bool, tagsAreEqual, (const std::string &, const std::string &), (const override));
};

struct CollisionContainerTest : testing::Test
{
    MockColliderComponentManagerBase manager;
    GameObject gameObject;
    std::string role{"role"};
    std::string roleOfInterest{"otherRole1"};
    size_t nColisions{1};
    std::set<CollisionType> collisions{CollisionType{roleOfInterest, nColisions}};
    DummyColliderDescriptor colliderDescriptor{std::make_unique<DummyColliderShape>(), role};
    ColliderComponentWithDummyShape collider{std::move(colliderDescriptor), &gameObject, &manager};
    CollisionInfo<DummyColliderShape> info{role, &collider, roleOfInterest, nColisions};
    std::unique_ptr<MockColliderTagsManager> tagsManager{std::make_unique<MockColliderTagsManager>()};
    MockColliderTagsManager *tagsManagerSpy{tagsManager.get()};
    std::unique_ptr<CollisionContainerWithDummyShape> container; //{std::move(tagsManager)};
    std::string dummyTag{"DummyTag"};
    void SetUp() override
    {
        container = std::make_unique<CollisionContainerWithDummyShape>(std::move(tagsManager));
    }
    void TearDown() override
    {
        Mock::VerifyAndClearExpectations(tagsManagerSpy);
        Mock::AllowLeak(tagsManagerSpy);
    }
};

TEST_F(CollisionContainerTest, UsesItsTagsManagerToBuildATagWhenACollisionIsInserted)
{
    EXPECT_CALL(*tagsManagerSpy, buildTag).Times(AtLeast(1));
    container->insertCollision(info);
}

TEST_F(CollisionContainerTest, CanAddACollision)
{
    ASSERT_FALSE(container->hasCollision(info));
    container->insertCollision(info);
    ASSERT_TRUE(container->hasCollision(info));
}

TEST_F(CollisionContainerTest, ReturnsANonEmptyTagIfTheCollisionExist)
{
    EXPECT_CALL(*tagsManagerSpy, buildTag).WillRepeatedly(Return(dummyTag));
    container->insertCollision(info);
    ASSERT_TRUE(container->hasCollision(info));
    auto tagForCollision{container->tagForCollision(info)};
    ASSERT_FALSE(tagForCollision->empty());
}
TEST_F(CollisionContainerTest, DoesntReturnATagIfTheCollisionDoesntExist)
{
    EXPECT_CALL(*tagsManagerSpy, buildTag).WillRepeatedly(Return(dummyTag));
    ASSERT_FALSE(container->hasCollision(info));
    auto tagForCollision{container->tagForCollision(info)};
    ASSERT_FALSE(tagForCollision.has_value());
}
TEST_F(CollisionContainerTest, KnowsMaxNumberOfCollisionsForColliderAndItsCollisionTag)
{
    container->insertCollision(info);
    auto tagForCollision{container->tagForCollision(info)};
    auto maxNumberOfCollisions{container->maxNumberOfCollisions(tagForCollision.value(), info.colliderComponent)};
    ASSERT_THAT(maxNumberOfCollisions.value(), Eq(info.maxNumberOfCollisions));
}
