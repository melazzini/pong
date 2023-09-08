#pragma once
#include "Component.h"
#include <memory>

template <typename TColliderShape> class ColliderComponentManagerBase : public ComponentManager
{
};

template <typename TColliderShape> class ColliderComponent : public Component
{
  public:
    ColliderComponent(std::unique_ptr<TColliderShape> colliderShape, GameObject *owner,
                      ColliderComponentManagerBase<TColliderShape> *manager)
        : Component{owner, manager}, m_shape{std::move(colliderShape)}
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

  protected:
    std::unique_ptr<TColliderShape> m_shape;
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
