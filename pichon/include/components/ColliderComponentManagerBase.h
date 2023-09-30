#pragma once
#include "ColliderTagsManager.h"
#include "Component.h"
#include "components/ColliderValidator.h"
#include "components/CollisionContainer.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename TColliderShape> struct ColliderComponent;

template <typename TColliderShape> class ColliderComponentManagerBase : public IComponentManager
{
  public:
    inline static int count{};
    ColliderComponentManagerBase(std::shared_ptr<IColliderTagsManager> tagsManager,
                                 std::unique_ptr<ICollisionContainer<TColliderShape>> container)
        : m_tagsManager{tagsManager}, m_collisionContainer{std::move(container)}
    {
    }

    bool hasComponent(IComponent *componet) const override
    {
        return false;
    }

    void destroyComponents() override
    {
    }

    bool registerComponent(IComponent *component) override
    {
        if (component)
        {
            m_components.push_back(component);
            return true;
        }
        return false;
    }

    void insertCollisionInfo(CollisionInfo<TColliderShape> info)
    {
        m_collisionContainer->insertCollisionInfo(info);
    }

    std::vector<OccurredCollisionInfo<TColliderShape>> colliders(ColliderComponent<TColliderShape> *thisCollider)
    {
        return m_collisionContainer->recordedColliders(thisCollider);
    }

    void updateComponents(uint32_t deltatime) override
    {
        clearCollisionRecords();
        recordInformationAboutOccurredCollisions();
        updateComponentsImpl(deltatime);
    }

  private:
    std::shared_ptr<IColliderTagsManager> m_tagsManager;
    std::unique_ptr<ICollisionContainer<TColliderShape>> m_collisionContainer;
    ColliderValidator<TColliderShape> m_validator;
    std::vector<IComponent *> m_components;

  private:
    void clearCollisionRecords()
    {
        m_collisionContainer->clearRecordedCollisions();
    }
    void updateComponentsImpl(uint32_t deltatime)
    {
        for (auto colliderRecordPair : m_collisionContainer->recordsOfAllCollisions())
        {
            colliderRecordPair.first->update(deltatime);
        }
    }

    struct CollidersSetWithRole
    {
        ColliderComponentContainer<TColliderShape> *colliders;
        std::string role;
    };

    std::pair<std::optional<ColliderComponentContainer<TColliderShape> *>,
              std::optional<ColliderComponentContainer<TColliderShape> *>>
    getCollidersPairByRoles(const std::string &roleA, const std::string &roleB)
    {
        return std::pair{m_collisionContainer->getCollidersByRole(roleA),
                         m_collisionContainer->getCollidersByRole(roleB)};
    }

    std::pair<std::string, std::string> getRolesForTag(const std::string &tag)
    {
        return m_tagsManager->getRolesForTag(tag);
    }

    bool bothColliderSetsExist(std::optional<ColliderComponentContainer<TColliderShape> *> setA,
                               std::optional<ColliderComponentContainer<TColliderShape> *> setB)
    {
        return setA.has_value() && setB.has_value();
    }

    std::optional<std::pair<CollidersSetWithRole, CollidersSetWithRole>> getCollidersWithRolesForTag(
        const std::string &tag)
    {
        auto [roleA, roleB]{getRolesForTag(tag)};
        auto [collidersA, collidersB]{getCollidersPairByRoles(roleA, roleB)};
        if (bothColliderSetsExist(collidersA, collidersB))
        {
            return std::pair{CollidersSetWithRole{collidersA.value(), roleA},
                             CollidersSetWithRole{collidersB.value(), roleB}};
        }
        return std::nullopt;
    }

    void recordCollisionIfTargetColliderIsInterested(ColliderComponent<TColliderShape> *targetCollider,
                                                     ColliderComponent<TColliderShape> *otherCollider,
                                                     const std::string &otherColliderRole)
    {
        if (m_validator.colliderIsInterestedInRecordingCollisions(targetCollider))
        {
            OccurredCollisionInfo<TColliderShape> info{otherColliderRole, otherCollider};
            m_collisionContainer->recordCollision(targetCollider, info);
        }
    }

    struct ColliderWithRole
    {
        ColliderComponent<TColliderShape> *collider;
        std::string role;
    };

    void recordCollisionForInterestedColliders(ColliderWithRole colliderA, ColliderWithRole colliderB)
    {
        recordCollisionIfTargetColliderIsInterested(colliderA.collider, colliderB.collider, colliderB.role);
        recordCollisionIfTargetColliderIsInterested(colliderB.collider, colliderA.collider, colliderA.role);
    }

    bool didCollidersCollide(ColliderComponent<TColliderShape> *colliderA,
                             ColliderComponent<TColliderShape> *colliderB) const
    {
        return colliderA->collidesWith(colliderB);
    }

    bool canColliderStillAcceptMoreCollisions(ColliderComponent<TColliderShape> *collider)
    {
        return m_validator.canColliderAcceptMoreCollisions(m_collisionContainer.get(), collider);
    }

    void evaluateCollisionOfColliderWithOtherColliders(ColliderWithRole colliderWithRole,
                                                       CollidersSetWithRole otherColliders)
    {
        forEachIf(
            std::begin(*(otherColliders.colliders)), std::end(*(otherColliders.colliders)),
            [this, &colliderWithRole] { return canColliderStillAcceptMoreCollisions(colliderWithRole.collider); },
            [otherColliderRole = otherColliders.role, this,
             &colliderWithRole](ColliderComponent<TColliderShape> *otherCollider) {
                if (canColliderStillAcceptMoreCollisions(otherCollider) &&
                    didCollidersCollide(colliderWithRole.collider, otherCollider))
                {
                    recordCollisionForInterestedColliders(colliderWithRole,
                                                          ColliderWithRole{otherCollider, otherColliderRole});
                }
            });
    }

    void evaluateCollisionsBetweenTwoSetsOfColliders(CollidersSetWithRole collidersA, CollidersSetWithRole collidersB)
    {
        for (auto colliderA : *(collidersA.colliders))
        {
            evaluateCollisionOfColliderWithOtherColliders(ColliderWithRole{colliderA, collidersA.role}, collidersB);
        }
    }

    void recordCollisionsForTag(const std::string &tag)
    {
        if (auto theTwoSetsOfColliders{getCollidersWithRolesForTag(tag)}; theTwoSetsOfColliders.has_value())
        {
            auto [setOfCollidersA, setOfCollidersB]{theTwoSetsOfColliders.value()};
            evaluateCollisionsBetweenTwoSetsOfColliders(setOfCollidersA, setOfCollidersB);
        }
    }

    void recordInformationAboutOccurredCollisions()
    {
        const std::unordered_set<std::string> &allTags = m_collisionContainer->getAllTags();
        for (const auto &tag : allTags)
        {
            recordCollisionsForTag(tag);
        }
    }
};
