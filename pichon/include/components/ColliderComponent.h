#pragma once
#include "Component.h"
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <tuple>

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

template <typename TColliderShape> class ColliderComponentManagerBase;

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

    void update(float deltatime) override
    {
        std::cout << "Updating ..." << std::endl;
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

