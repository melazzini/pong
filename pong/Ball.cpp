#include "Ball.h"
#include "Game.h"
#include "Interfaces.h"
#include "RectangularColliderComponentManager.h"
#include "RectangularGeometry.h"
#include "components/DrawableComponent.h"
#include "components/TransformComponent.h"

Game *gameInstance{};
bool collided = false;
int counter = 0;
struct BallTransformComponent : TransformComponent
{
    static constexpr int v = 500;
    BallTransformComponent(GameObject *owner) : TransformComponent{owner, TransformComponentManager::getInstance()}
    {
        m_velocityX = v;
        m_velocityY = -v;
    }

    void update(uint32_t deltatime) override
    {
        auto pos{position()};
        auto currentX{pos.x};
        auto currentY{pos.y};
        if (currentX <= 30 && m_velocityX <= 0)
        {
            setPosition(
                {(m_velocityX * int(deltatime)) / 2000 + currentX, (m_velocityY * int(deltatime)) / 1000 + currentY});
        }
        else
        {
            setPosition(
                {(m_velocityX * int(deltatime)) / 1000 + currentX, (m_velocityY * int(deltatime)) / 1000 + currentY});
        }

        if (position().x < 0)
        {
            gameInstance->terminate();
        }
    }

    void moveDown()
    {
        m_velocityY = v;
    }
    void moveUp()
    {
        m_velocityY = -v;
    }

    void moveLeft()
    {
        m_velocityX = -v;
    }
    void moveRight()
    {
        m_velocityX = v;
    }

  private:
    int m_velocityX;
    int m_velocityY;
};

struct MyBallRectangularCollider : RectangularColliderComponent
{
    MyBallRectangularCollider(RectangularColliderDescriptor descriptor, GameObject *owner,
                              RectangularColliderComponentManager *manager_)
        : RectangularColliderComponent(std::move(descriptor), owner, manager_)
    {
        manager_->insertCollisionInfo(RectangularColliderCollisionInfo{"ball", this, "paddle"});
        manager_->insertCollisionInfo(RectangularColliderCollisionInfo{"ball", this, "TopWall"});
        manager_->insertCollisionInfo(RectangularColliderCollisionInfo{"ball", this, "BottomWall"});
        manager_->insertCollisionInfo(RectangularColliderCollisionInfo{"ball", this, "RightWall"});
        setMaxNumberOfCollisions(1);
        m_owner = owner;
        m_manager = manager_;
    }
    void update(uint32_t deltatime) override
    {
        auto transformComponent = m_owner->component<BallTransformComponent>();
        m_shape->setPosition(transformComponent->position());
        RectangularGeometry size_{transformComponent->size().width(), transformComponent->size().height()};
        m_shape->setSize(size_);
        if (auto colliders{m_manager->colliders(this)}; !colliders.empty())
        {
            for (auto &col_info : colliders)
            {
                if (col_info.roleOfOtherCollider == "TopWall")
                {
                    transformComponent->moveDown();
                }
                else if (col_info.roleOfOtherCollider == "BottomWall")
                {
                    transformComponent->moveUp();
                }
                else if (col_info.roleOfOtherCollider == "RightWall")
                {
                    transformComponent->moveLeft();
                }
                else if (col_info.roleOfOtherCollider == "paddle")
                {
                    transformComponent->moveRight();
                }
            }
        }
    }

  private:
    GameObject *m_owner;
    RectangularColliderComponentManagerBase *m_manager;
    std::string m_lastCollider;
};
Ball::Ball(IRenderer *renderer)
{
    auto transform = addComponent<BallTransformComponent>(this);
    // transform->setPosition(glm::ivec2{WINDOW_SIZE.width() / 2, WINDOW_SIZE.height() / 2});
    transform->setPosition(glm::ivec2{250, 150});
    transform->setSize(RectangularGeometry{20, 20});
    auto drawableComponent{addComponent<BallDrawableComponent>(this, DrawableComponentManager::getInstance(renderer))};
    auto ll{addComponent<MyBallRectangularCollider>(
        RectangularColliderDescriptor{std::make_unique<Boxcollidershape>(), "ball"}, this,
        RectangularColliderComponentManager::getInstance())};
}

