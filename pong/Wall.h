#pragma once
#include "GameObject.h"
#include "Interfaces.h"
#include "RectangularColliderComponentManager.h"
#include "SimpleShapes.h"
#include "components/ColliderComponent.h"
#include "components/TransformComponent.h"
#include <memory>
#include <type_traits>

struct Wall;

struct WallCollider : RectangularColliderComponent
{
    WallCollider(RectangularColliderDescriptor descriptor, GameObject *owner,
                 RectangularColliderComponentManager *manager_, std::string tag)
        : RectangularColliderComponent(std::move(descriptor), owner, manager_)
    {
        // manager_->insertCollisionInfo(RectangularColliderCollisionInfo{tag, this, "paddle"});
        manager_->insertCollisionInfo(RectangularColliderCollisionInfo{tag, this, "ball"});
        setMaxNumberOfCollisions(0);
        m_owner = owner;
        m_manager = manager_;
    }

    void update(uint32_t deltatime) override
    {
        using fmt::format;
        auto transformComponent = m_owner->component<TransformComponent>();
        m_shape->setPosition(transformComponent->position());
        m_shape->setSize(transformComponent->size());
    }

  private:
    GameObject *m_owner;
    RectangularColliderComponentManagerBase *m_manager;
};

struct WallDrawable : DrawableComponent
{
    WallDrawable(GameObject *owner, DrawableComponentManagerBase *manager)
        : DrawableComponent{owner, manager}, m_transformComponent{nullptr},
          m_shape(glm::ivec2{100, 100}, RectangularGeometry{20, 100})
    {
        m_drawable = &m_shape;
        m_transformComponent = owner->component<TransformComponent>();
        m_shape.setBackgroundColor(glm::u8vec4{100, 100, 100, 255});
    }

    void update(uint32_t deltatime) override
    {
        m_shape.setWidth(m_transformComponent->size().width());
        m_shape.setHeight(m_transformComponent->size().height());
        m_shape.setPosition(m_transformComponent->position());
    }

    void setColor(glm::u8vec4 color)
    {
        m_shape.setBackgroundColor(color);
    }

  private:
    TransformComponent *m_transformComponent;
    RectangularShape m_shape;
};

class Wall : public GameObject
{
  public:
    explicit Wall(IRenderer *renderer, glm::ivec2 position, RectangularGeometry size, std::string tag)
    {
        addComponent<TransformComponent>(this, TransformComponentManager::getInstance(), position, size);
        addComponent<WallDrawable>(this, DrawableComponentManager::getInstance(renderer));
        addComponent<WallCollider>(RectangularColliderDescriptor{std::make_unique<Boxcollidershape>(), tag}, this,
                                   RectangularColliderComponentManager::getInstance(), std::move(tag));
    }
};

