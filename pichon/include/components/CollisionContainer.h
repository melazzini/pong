#pragma once
#include "ColliderComponent.h"
#include "utils.h"
#include <list>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>

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
        auto [possibleTag1, possibleTag2]{buildPossibleTags(collisionInfo.colliderRole, collisionInfo.roleOfInterest)};
        if (!containsAnyOfThePossibleTags(possibleTag1, possibleTag2))
        {
            m_tags.emplace(possibleTag1);
            m_maxNumberOfCollisions[std::pair{possibleTag1, collisionInfo.colliderComponent}] =
                collisionInfo.maxNumberOfCollisions;
        }
    }

    bool hasCollision(const CollisionInfo<TColliderShape> &collisionInfo) override
    {
        auto [possibleTag1, possibleTag2]{buildPossibleTags(collisionInfo.colliderRole, collisionInfo.roleOfInterest)};
        if (!containsAnyOfThePossibleTags(possibleTag1, possibleTag2))
        {
            return false;
        }
        return true;
    }

    std::optional<std::string> tagForCollision(const CollisionInfo<TColliderShape> &collisionInfo) override
    {
        auto [possibleTag1, possibleTag2]{buildPossibleTags(collisionInfo.colliderRole, collisionInfo.roleOfInterest)};
        if (!containsAnyOfThePossibleTags(possibleTag1, possibleTag2))
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
