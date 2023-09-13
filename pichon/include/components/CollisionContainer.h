#pragma once
#include "ColliderComponent.h"
#include "ColliderTagsManager.h"
#include "utils.h"
#include <cstdlib>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename TColliderShape> struct CollisionInfo
{
    std::string colliderRole{};
    ColliderComponent<TColliderShape> *colliderComponent{};
    std::string roleOfInterest{};
};

template <typename TColliderShape> struct OccurredCollisionInfo
{
    std::string roleOfOtherCollider;
    ColliderComponent<TColliderShape> *otherCollider;
};

template <typename TColliderShape> struct ICollisionContainer
{
    virtual void insertCollisionInfo(CollisionInfo<TColliderShape> collisionInfo) = 0;
    virtual void recordCollision(ColliderComponent<TColliderShape> *collider,
                                 OccurredCollisionInfo<TColliderShape>) = 0;
    [[nodiscard]] virtual bool hasCollision(const CollisionInfo<TColliderShape> &collisionInfo) const = 0;
    [[nodiscard]] virtual bool colliderHasRecordOfCollisions(ColliderComponent<TColliderShape> *) const = 0;
    virtual std::optional<size_t> numberOfRecordedCollisionsForCollider(ColliderComponent<TColliderShape> *) const = 0;
    virtual std::optional<std::string> tagForCollision(const CollisionInfo<TColliderShape> &collisionInfo) const = 0;
    virtual std::optional<std::unordered_set<ColliderComponent<TColliderShape> *> *> getCollidersByRole(
        const std::string &role) = 0;
    virtual const std::unordered_map<ColliderComponent<TColliderShape> *,
                                     std::vector<OccurredCollisionInfo<TColliderShape>>>
        &recordsOfAllCollisions() const = 0;

    virtual const std::unordered_set<std::string> &getAllTags() const = 0;
    virtual void clearRecordedCollisions() = 0;
    virtual std::vector<OccurredCollisionInfo<TColliderShape>> recordedColliders(
        ColliderComponent<TColliderShape> *) = 0;
};

template <typename TColliderShape> class CollisionContainer : public ICollisionContainer<TColliderShape>
{
  public:
    CollisionContainer(std::shared_ptr<IColliderTagsManager> tagsManager) : m_colliderTagsManager{tagsManager}
    {
    }
    void insertCollisionInfo(CollisionInfo<TColliderShape> collisionInfo) override
    {
        auto [possibleTag1, possibleTag2]{buildPossibleTags(collisionInfo.colliderRole, collisionInfo.roleOfInterest)};
        if (possibleTag1.empty() || possibleTag2.empty())
        {
            throw std::runtime_error{"Received empty tags from the tags manager!"};
        }
        if (!containsAnyOfThePossibleTags(possibleTag1, possibleTag2))
        {
            m_tags.emplace(possibleTag1);
        }
        m_collidersByRole[collisionInfo.colliderRole].emplace(collisionInfo.colliderComponent);
        m_recordsOfCollisionsForEachCollider[collisionInfo.colliderComponent];
    }
    virtual void recordCollision(ColliderComponent<TColliderShape> *collider,
                                 OccurredCollisionInfo<TColliderShape> info) override
    {
        m_recordsOfCollisionsForEachCollider[collider].emplace_back(std::move(info));
    }

    bool hasCollision(const CollisionInfo<TColliderShape> &collisionInfo) const override
    {
        auto [possibleTag1, possibleTag2]{buildPossibleTags(collisionInfo.colliderRole, collisionInfo.roleOfInterest)};
        if (!containsAnyOfThePossibleTags(possibleTag1, possibleTag2))
        {
            return false;
        }
        return true;
    }
    virtual bool colliderHasRecordOfCollisions(ColliderComponent<TColliderShape> *collider) const override
    {
        return m_recordsOfCollisionsForEachCollider.contains(collider);
    }

    virtual std::optional<size_t> numberOfRecordedCollisionsForCollider(
        ColliderComponent<TColliderShape> *collider) const override
    {
        if (m_recordsOfCollisionsForEachCollider.contains(collider))
        {
            return m_recordsOfCollisionsForEachCollider.at(collider).size();
        }
        return std::nullopt;
    }

    std::optional<std::string> tagForCollision(const CollisionInfo<TColliderShape> &collisionInfo) const override
    {
        auto [possibleTag1, possibleTag2]{buildPossibleTags(collisionInfo.colliderRole, collisionInfo.roleOfInterest)};
        if (!containsAnyOfThePossibleTags(possibleTag1, possibleTag2))
        {
            return std::nullopt;
        }
        return possibleTag1;
    }

    std::optional<std::unordered_set<ColliderComponent<TColliderShape> *> *> getCollidersByRole(
        const std::string &role) override
    {
        if (m_collidersByRole.contains(role))
        {
            return &m_collidersByRole.at(role);
        }
        return std::nullopt;
    }

    const std::unordered_set<std::string> &getAllTags() const override
    {
        return m_tags;
    }

    virtual const std::unordered_map<ColliderComponent<TColliderShape> *,
                                     std::vector<OccurredCollisionInfo<TColliderShape>>>
        &recordsOfAllCollisions() const override
    {
        return m_recordsOfCollisionsForEachCollider;
    }

    void clearRecordedCollisions() override
    {
        for (auto &colliderPair : m_recordsOfCollisionsForEachCollider)
        {
            colliderPair.second.clear();
        }
    }

    std::vector<OccurredCollisionInfo<TColliderShape>> recordedColliders(
        ColliderComponent<TColliderShape> *interestedCollider) override
    {
        return std::move(m_recordsOfCollisionsForEachCollider[interestedCollider]);
    }

  private:
    std::shared_ptr<IColliderTagsManager> m_colliderTagsManager;
    std::unordered_set<std::string> m_tags;
    std::unordered_map<std::string, std::unordered_set<ColliderComponent<TColliderShape> *>> m_collidersByRole;
    std::unordered_map<ColliderComponent<TColliderShape> *, std::vector<OccurredCollisionInfo<TColliderShape>>>
        m_recordsOfCollisionsForEachCollider;

  private:
    std::pair<std::string, std::string> buildPossibleTags(const std::string &roleA, const std::string &roleB) const
    {
        auto possibleTag1{m_colliderTagsManager->buildTag(roleA, roleB)};
        auto possibleTag2{m_colliderTagsManager->buildTag(roleB, roleA)};
        return {possibleTag1, possibleTag2};
    }

    bool containsAnyOfThePossibleTags(const std::string &tag1, const std::string &tag2) const
    {
        return (m_tags.contains(tag1) || m_tags.contains(tag2));
    }
};
