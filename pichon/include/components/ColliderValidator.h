#pragma once
#include "CollisionContainer.h"
#include "components/ColliderComponent.h"

template <typename TColliderShape> struct IColliderValidator
{

    [[nodiscard]] virtual bool canColliderAcceptMoreCollisions(const ICollisionContainer<TColliderShape> *container,
                                                               ColliderComponent<TColliderShape> *) const = 0;
    [[nodiscard]] virtual bool colliderIsInterestedInRecordingCollisions(
        const ColliderComponent<TColliderShape> *) const = 0;

    virtual ~IColliderValidator() = default;
};

template <typename TColliderShape> class ColliderValidator : public IColliderValidator<TColliderShape>
{
  public:
    bool canColliderAcceptMoreCollisions(const ICollisionContainer<TColliderShape> *container,
                                         ColliderComponent<TColliderShape> *collider) const override
    {
        if (collider->maxNumberOfCollisions() == 0)
        {
            return true;
        }
        if (container->numberOfRecordedCollisionsForCollider(collider).has_value())
        {
            return container->numberOfRecordedCollisionsForCollider(collider) < collider->maxNumberOfCollisions();
        }

        return false;
    }

    bool colliderIsInterestedInRecordingCollisions(const ColliderComponent<TColliderShape> *collider) const override
    {
        return collider->maxNumberOfCollisions() > 0;
    }
};
