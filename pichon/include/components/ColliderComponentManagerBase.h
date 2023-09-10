#pragma once
#include "ColliderTagsManager.h"
#include "Component.h"
#include "components/CollisionContainer.h"
#include <iomanip>
#include <iostream>
#include <memory>
#include <set>
#include <unordered_set>

template <typename TColliderShape> struct ColliderComponent;

template <typename TColliderShape> class ColliderComponentManagerBase : public ComponentManager
{
  public:
    ColliderComponentManagerBase(std::shared_ptr<IColliderTagsManager> tagsManager,
                                 std::unique_ptr<ICollisionContainer<TColliderShape>> container)
        : m_tagsManager{tagsManager}, m_collisionContainer{std::move(container)}
    {
    }

    //    [[nodiscard]] const std::set<std::string> &collisionTags() const
    //    {
    //    }
    //
    //    [[nodiscard]] std::set<std::string> collisionTagsFor(
    //        const ColliderComponent<TColliderShape> &colliderComponent) const;
    //
    void registerComponent(Component *component) override
    {
        ComponentManager::registerComponent(component);
    }

    void update(float deltatime) override
    {
        std::cout << "ColliderComponentManagerBase: " << __FUNCTION__ << std::endl;
        const std::unordered_set<std::string> &allTags = m_collisionContainer->getAllTags();
        for (const auto &tag : allTags)
        {
            auto [roleA, roleB]{m_tagsManager->getRolesForTag(tag)};
            auto collidersA = m_collisionContainer->getCollidersByRole(roleA);
            auto collidersB = m_collisionContainer->getCollidersByRole(roleB);
            if (collidersA.has_value() && collidersB.has_value())
            {
                std::cout << "Size of CollidersA: " << collidersA.value()->size() << std::endl;
                std::cout << "Size of CollidersB: " << collidersB.value()->size() << std::endl;

                std::unordered_set<ColliderComponent<TColliderShape> *> *setOfCollidersA(collidersA.value());
                std::unordered_set<ColliderComponent<TColliderShape> *> *setOfCollidersB(collidersB.value());

                for (auto colliderA_i : *setOfCollidersA)
                {
                    std::cout << "ColliderA_i: " << colliderA_i << std::endl;
                    for (auto colliderB_j : *setOfCollidersB)
                    {
                        std::cout << "ColliderB_i: " << colliderB_j << std::endl;
                        std::cout << "ColliderA_i collides with ColliderB_i?: "
                                  << colliderA_i->collidesWith(*colliderB_j) << std::endl;
                    }
                }
            }
        }
    }

  private:
    std::shared_ptr<IColliderTagsManager> m_tagsManager;
    std::unique_ptr<ICollisionContainer<TColliderShape>> m_collisionContainer;
};

// template <typename TColliderShape>
// std::set<std::string> ColliderComponentManagerBase<TColliderShape>::collisionTagsFor(
//     const ColliderComponent<TColliderShape> &colliderComponent) const
//{
//     return m_tags;
// }
//
// template <typename TColliderShape>
// void ColliderComponentManagerBase<TColliderShape>::registerComponent(Component *component)
//{
//     ComponentManager::registerComponent(component);
//
//     dynamic_cast<ColliderComponent<TColliderShape> *>(component);
//     m_tags.emplace("yeah!");
// }
