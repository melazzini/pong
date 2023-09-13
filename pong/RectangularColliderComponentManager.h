#pragma once
#include "components/ColliderComponent.h"
#include "components/ColliderComponentManagerBase.h"
#include <cstdlib>
#include <iostream>

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

struct MyRectangularCollider : RectangularColliderComponent
{
    MyRectangularCollider(RectangularColliderDescriptor descriptor, GameObject *owner,
                          RectangularColliderComponentManager *manager_)
        : RectangularColliderComponent(std::move(descriptor), owner, manager_)
    {
        manager_->insertCollisionInfo(RectangularColliderCollisionInfo{"paddle", this, "ball"});
        setMaxNumberOfCollisions(1);
    }

    void update(float deltatime) override
    {
        std::cout << "Hello paddle!" << std::endl;
    }
};

struct MyBallRectangularCollider : RectangularColliderComponent
{
    MyBallRectangularCollider(RectangularColliderDescriptor descriptor, GameObject *owner,
                              RectangularColliderComponentManager *manager_)
        : RectangularColliderComponent(std::move(descriptor), owner, manager_)
    {
        manager_->insertCollisionInfo(RectangularColliderCollisionInfo{"ball", this, "paddle"});
        setMaxNumberOfCollisions(1);
    }
    void update(float deltatime) override
    {
        std::cout << "Hello ball!" << std::endl;
    }
};
