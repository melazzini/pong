#pragma once
#include "Component.h"
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <tuple>

struct IColliderTagsManager
{
    [[nodiscard]] virtual std::string buildTag(const std::string &colliderRoleA,
                                               const std::string &colliderRoleB) const = 0;
    [[nodiscard]] virtual bool tagsAreEqual(const std::string &tagA, const std::string &tagB) const = 0;
    [[nodiscard]] virtual std::pair<std::string, std::string> getRolesForTag(const std::string &tag) const = 0;
    [[nodiscard]] virtual bool validTag(const std::string &tag) const = 0;
    virtual ~IColliderTagsManager() = default;
};

class SimpleColliderTagsManager : public IColliderTagsManager
{
  public:
    inline static const std::string SEPARATOR{"_"};
    std::string buildTag(const std::string &colliderRoleA, const std::string &colliderRoleB) const override;
    bool tagsAreEqual(const std::string &tagA, const std::string &tagB) const override;
    std::pair<std::string, std::string> getRolesForTag(const std::string &tag) const override;
    bool validTag(const std::string &tag) const override;
};

template <typename TColliderShape> struct ColliderComponent;

template <typename TColliderShape> class ColliderComponentManagerBase : public ComponentManager
{
  public:
    [[nodiscard]] const std::set<std::string> &collisionTags() const
    {
    }

    [[nodiscard]] std::set<std::string> collisionTagsFor(
        const ColliderComponent<TColliderShape> &colliderComponent) const;

    void registerComponent(Component *component) override;

  private:
    std::set<std::string> m_tags;
};

struct CollisionType
{
    std::string roleOfInterest{""};
    size_t maxNumberOfCollisions{};

    bool operator<(const CollisionType &other) const
    {

        return std::pair<std::string, int>{roleOfInterest, maxNumberOfCollisions} <
               std::pair<std::string, int>{other.roleOfInterest, maxNumberOfCollisions};
    }

    bool operator==(const CollisionType &other) const
    {
        return (roleOfInterest == other.roleOfInterest) && (maxNumberOfCollisions == other.maxNumberOfCollisions);
    }
};

template <typename TColliderShape> struct ColliderDescriptor
{
    std::unique_ptr<TColliderShape> colliderShape;
    std::string role;
    std::set<CollisionType> collisions;
};

template <typename TColliderShape> class ColliderComponent : public Component
{
  public:
    ColliderComponent(ColliderDescriptor<TColliderShape> colliderDescriptor, GameObject *owner,
                      ColliderComponentManagerBase<TColliderShape> *manager)
        : Component{owner, manager}, m_shape{std::move(colliderDescriptor.colliderShape)},
          m_role{std::move(

              colliderDescriptor.role)},
          m_collisionTypes{std::move(colliderDescriptor.collisions)}
    {
    }
    bool collidesWith(const ColliderComponent<TColliderShape> &other) const
    {
        return m_shape->collidesWith(*other.m_shape);
    }

    const std::unique_ptr<TColliderShape> &shape() const
    {
        return m_shape;
    }

    const std::string &role() const
    {
        return m_role;
    }

    bool hasCollision(const CollisionType &collision) const
    {
        return m_collisionTypes.contains(collision);
    }

    const std::set<CollisionType> &collisions() const
    {
        return m_collisionTypes;
    }

  private:
    std::unique_ptr<TColliderShape> m_shape;
    std::string m_role;
    std::set<CollisionType> m_collisionTypes;
};

class Boxcollidershape
{
  public:
    bool collideswith(const Boxcollidershape &other) const
    {
        return false;
    };
};

class CircularColliderShape
{
  public:
    bool collideswith(const CircularColliderShape &other) const
    {
        return false;
    };
};

using CircularColliderComponet = ColliderComponent<CircularColliderShape>;
using RectangularColliderComponent = ColliderComponent<Boxcollidershape>;

template <typename TColliderShape>
std::set<std::string> ColliderComponentManagerBase<TColliderShape>::collisionTagsFor(
    const ColliderComponent<TColliderShape> &colliderComponent) const
{
    return m_tags;
}

template <typename TColliderShape>
void ColliderComponentManagerBase<TColliderShape>::registerComponent(Component *component)
{
    ComponentManager::registerComponent(component);

    dynamic_cast<ColliderComponent<TColliderShape> *>(component);
    m_tags.emplace("yeah!");
}

