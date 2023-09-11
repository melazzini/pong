#pragma once
#include "components/ColliderComponent.h"
#include "components/ColliderComponentManagerBase.h"

using RectangularColliderComponentManagerBase = ColliderComponentManagerBase<Boxcollidershape>;
using RectangularCollisionContainer = CollisionContainer<Boxcollidershape>;
using RectangularColliderDescriptor = ColliderDescriptor<Boxcollidershape>;
using RectangularColliderCollisionInfo = CollisionInfo<Boxcollidershape>;

class RectangularColliderComponentManager : public RectangularColliderComponentManagerBase
{
  public:
    static RectangularColliderComponentManager *getInstance()
    {
        static RectangularColliderComponentManager instance{std::make_shared<SimpleColliderTagsManager>()};
        return &instance;
    }

  private:
    RectangularColliderComponentManager(std::shared_ptr<SimpleColliderTagsManager> tagsManager)
        : RectangularColliderComponentManagerBase{tagsManager,
                                                  std::make_unique<RectangularCollisionContainer>(tagsManager)}
    {
    }
};
