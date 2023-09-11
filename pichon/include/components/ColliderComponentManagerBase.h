#pragma once
#include "ColliderTagsManager.h"
#include "Component.h"
#include "components/ColliderValidator.h"
#include "components/CollisionContainer.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <set>
#include <unordered_map>
#include <unordered_set>

template <typename TColliderShape> struct ColliderComponent;

template <typename TColliderShape> class ColliderComponentManagerBase : public ComponentManager
{
  public:
    inline static int count{};
    ColliderComponentManagerBase(std::shared_ptr<IColliderTagsManager> tagsManager,
                                 std::unique_ptr<ICollisionContainer<TColliderShape>> container)
        : m_tagsManager{tagsManager}, m_collisionContainer{std::move(container)}
    {
    }

    void registerComponent(Component *component) override
    {
        ComponentManager::registerComponent(component);
    }

    void insertCollisionInfo(CollisionInfo<TColliderShape> info)
    {
        m_collisionContainer->insertCollisionInfo(info);
    }

    void update(float deltatime) override
    {
        std::cout << "Updating the ColliderComponentManagerBase!!!!" << std::endl;
        m_collisionContainer->clearRecordedCollisions();
        const std::unordered_set<std::string> &allTags = m_collisionContainer->getAllTags();
        for (const auto &tag : allTags)
        {
            auto [roleA, roleB]{m_tagsManager->getRolesForTag(tag)};
            auto collidersA = m_collisionContainer->getCollidersByRole(roleA);
            auto collidersB = m_collisionContainer->getCollidersByRole(roleB);

            if (collidersA.has_value() && collidersB.has_value())
            {
                std::unordered_set<ColliderComponent<TColliderShape> *> *setOfCollidersA(collidersA.value());
                std::unordered_set<ColliderComponent<TColliderShape> *> *setOfCollidersB(collidersB.value());

                for (auto col_A : *setOfCollidersA)
                {
                    if (!m_validator.canColliderAcceptMoreCollisions(m_collisionContainer.get(), col_A))
                    {
                        continue;
                    }
                    std::cout << "Can collider" << std::endl;

                    for (auto col_B : *setOfCollidersB)
                    {
                        if (!m_validator.canColliderAcceptMoreCollisions(m_collisionContainer.get(), col_B))
                        {
                            continue;
                        }
                        if (col_A->collidesWith(col_B))
                        {
                            if (m_validator.colliderIsInterestedInRecordingCollisions(col_A))
                            {
                                std::cout << "Can colliderAAAA" << std::endl;
                                OccurredCollisionInfo<TColliderShape> infoA{roleB, col_B};
                                m_collisionContainer->recordCollision(col_A, infoA);
                            }
                            if (m_validator.colliderIsInterestedInRecordingCollisions(col_B))
                            {
                                std::cout << "Can colliderBBBB" << std::endl;
                                OccurredCollisionInfo<TColliderShape> infoB{roleA, col_A};
                                m_collisionContainer->recordCollision(col_B, infoB);
                            }
                        }
                        if (!m_validator.canColliderAcceptMoreCollisions(m_collisionContainer.get(), col_A))
                        {
                            break;
                        }
                    }
                }
            }
        }

        for (auto colliderRecordPair : m_collisionContainer->recordsOfAllCollisions())
        {
            if (!colliderRecordPair.second.empty())
            {
                colliderRecordPair.first->update(deltatime);
            }
        }
    }

  private:
    std::shared_ptr<IColliderTagsManager> m_tagsManager;
    std::unique_ptr<ICollisionContainer<TColliderShape>> m_collisionContainer;
    ColliderValidator<TColliderShape> m_validator;
};
