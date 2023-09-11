#pragma once
#include "ColliderComponent.h"
#include "ColliderTagsManager.h"
#include "utils.h"
#include <list>
#include <optional>
#include <stdexcept>
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
    [[nodiscard]] virtual bool hasCollision(const CollisionInfo<TColliderShape> &collisionInfo) const = 0;
    virtual std::optional<std::string> tagForCollision(const CollisionInfo<TColliderShape> &collisionInfo) const = 0;
    virtual std::optional<size_t> maxNumberOfCollisions(const std::string &colliderTag,
                                                        const ColliderComponent<TColliderShape> *collider) const = 0;
    virtual std::optional<std::unordered_set<ColliderComponent<TColliderShape> *> *> getCollidersByRole(
        const std::string &role) = 0;

    virtual const std::unordered_set<std::string> &getAllTags() const = 0;
};

template <typename TColliderShape> class CollisionContainer : public ICollisionContainer<TColliderShape>
{
  public:
    CollisionContainer(std::shared_ptr<IColliderTagsManager> tagsManager) : m_colliderTagsManager{tagsManager}
    {
    }
    void insertCollision(CollisionInfo<TColliderShape> collisionInfo) override
    {
        auto [possibleTag1, possibleTag2]{buildPossibleTags(collisionInfo.colliderRole, collisionInfo.roleOfInterest)};
        if (possibleTag1.empty() || possibleTag2.empty())
        {
            throw std::runtime_error{"Received empty tags from the tags manager!"};
        }
        if (!containsAnyOfThePossibleTags(possibleTag1, possibleTag2))
        {
            m_tags.emplace(possibleTag1);
            m_numberOfCollisions[std::pair{possibleTag1, collisionInfo.colliderComponent}] =
                std::pair<size_t, size_t>{0, collisionInfo.maxNumberOfCollisions};
            m_collidersByRole[collisionInfo.colliderRole].emplace(collisionInfo.colliderComponent);
        }
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

    std::optional<std::string> tagForCollision(const CollisionInfo<TColliderShape> &collisionInfo) const override
    {
        auto [possibleTag1, possibleTag2]{buildPossibleTags(collisionInfo.colliderRole, collisionInfo.roleOfInterest)};
        if (!containsAnyOfThePossibleTags(possibleTag1, possibleTag2))
        {
            return std::nullopt;
        }
        return possibleTag1;
    }

    std::optional<size_t> maxNumberOfCollisions(const std::string &colliderTag,
                                                const ColliderComponent<TColliderShape> *collider) const override
    {
        if (m_numberOfCollisions.contains({colliderTag, collider}))
        {
            return m_numberOfCollisions.at({colliderTag, collider}).second;
        }
        return std::nullopt;
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

  private:
    std::shared_ptr<IColliderTagsManager> m_colliderTagsManager;
    std::unordered_set<std::string> m_tags;
    std::unordered_map<std::string, std::unordered_set<ColliderComponent<TColliderShape> *>> m_collidersByRole;
    std::unordered_map<std::pair<std::string, const ColliderComponent<TColliderShape> *>, std::pair<size_t, size_t>,
                       hash_pair>
        m_numberOfCollisions;
    std::unordered_map<ColliderComponent<TColliderShape> *,
                       std::list<std::pair<std::string, ColliderComponent<TColliderShape> *>>>
        m_collidersToBeUpdated;

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
