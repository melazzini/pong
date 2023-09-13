#pragma once
#include "Component.h"
#include "RectangularGeometry.h"
#include <glm/glm.hpp>
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
          m_collisionTypes{std::move(colliderDescriptor.collisions)}, m_maxNumberOfCollisions{0}
    {
    }
    bool collidesWith(const ColliderComponent<TColliderShape> *other) const
    {
        return m_shape->collidesWith(*other->m_shape);
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
        std::cout << "Updating ... my friend!" << std::endl;
    }

    size_t maxNumberOfCollisions() const
    {
        return m_maxNumberOfCollisions;
    }

    virtual void setMaxNumberOfCollisions(size_t n)
    {
        m_maxNumberOfCollisions = n;
    }

  protected:
    std::unique_ptr<TColliderShape> m_shape;

  private:
    std::string m_role;
    std::set<CollisionType> m_collisionTypes;
    size_t m_maxNumberOfCollisions;
};

class Boxcollidershape
{
  public:
    explicit Boxcollidershape() = default;

    void setPosition(glm::ivec2 pos)
    {
        m_x = pos.x;
        m_y = pos.y;
    }

    void setSize(const RectangularGeometry &size)
    {
        m_w = size.width();
        m_h = size.height();
    }

    bool collidesWith(const Boxcollidershape &other) const
    {
        std::cout << "x,y:  " << m_x << ", " << m_y << std::endl;
        std::cout << "w,h:  " << m_w << ", " << m_h << std::endl;
        std::cout << "other.x,y:  " << other.m_x << ", " << other.m_y << std::endl;
        std::cout << "other.w,h:  " << other.m_w << ", " << other.m_h << std::endl;
        return (m_x + m_w >= other.m_x && m_y + m_h >= other.m_y) &&
               (other.m_x + other.m_w >= m_x && other.m_y + other.m_h >= m_y);
    };

  private:
    int m_x;
    int m_y;
    int m_w;
    int m_h;
};

class CircularColliderShape
{
  public:
    bool collidesWith(const CircularColliderShape &other) const
    {
        return false;
    };
};

using CircularColliderComponet = ColliderComponent<CircularColliderShape>;
using RectangularColliderComponent = ColliderComponent<Boxcollidershape>;

