#pragma once
#include "GameObject.h"
#include "components/ColliderComponent.h"
#include "components/ColliderComponentManagerBase.h"
#include "components/TransformComponent.h"
#include <cstdlib>
#include <fmt/core.h>
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
        m_owner = owner;
        m_manager = manager_;
    }

    void update(uint32_t deltatime) override
    {
        using fmt::format;
        auto transformComponent = m_owner->component<TransformComponent>();

        m_shape->setPosition(transformComponent->position());
        RectangularGeometry size_{transformComponent->size().width() + 10, transformComponent->size().height()};
        m_shape->setSize(size_);
        m_shape->setSize(size_);
        if (auto colliders{m_manager->colliders(this)}; !colliders.empty())
        {
            for (auto &col_info : colliders)
            {
                //                std::cout << col_info.otherCollider << "     " << col_info.roleOfOtherCollider <<
                //                std::endl;
            }
        }
    }

  private:
    GameObject *m_owner;
    RectangularColliderComponentManagerBase *m_manager;
};

