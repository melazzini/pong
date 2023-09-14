#include "Ball.h"
#include "Game.h"
#include "Interfaces.h"
#include "RectangularColliderComponentManager.h"
#include "RectangularGeometry.h"
#include "components/DrawableComponent.h"
#include "components/TransformComponent.h"

GameBase *gameInstance{};

struct BallTransformComponent : TransformComponent
{
    BallTransformComponent(GameObject *owner) : TransformComponent{owner, TransformComponentManager::getInstance()}
    {
        m_velocityX = 200;
        m_velocityY = -200;
    }

    void update(uint32_t deltatime) override
    {
        auto pos{position()};
        auto currentX{pos.x};
        auto currentY{pos.y};
        setPosition({(m_velocityX * int(deltatime)) / 1000 + currentX, (m_velocityY * int(deltatime)) / 1000 + currentY});

        if (position().x < 0)
        {
            gameInstance->setRunning(false);
        }
    }

    void moveDown()
    {
        m_velocityY = 150;
    }
    void moveUp()
    {
        m_velocityY = -150;
    }

    void moveLeft()
    {
        m_velocityX = -150;
    }
    void moveRight()
    {
        m_velocityX = 150;
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
        m_shape->setSize(transformComponent->size());
        if (auto colliders{m_manager->colliders(this)}; !colliders.empty())
        {
            for (auto &col_info : colliders)
            {
                if (col_info.roleOfOtherCollider == "TopWall")
                {
                    // std::cout << "Role: " << col_info.roleOfOtherCollider << std::endl;
                    transformComponent->moveDown();
                }
                else if (col_info.roleOfOtherCollider == "BottomWall")
                {
                    // std::cout << "Role: " << col_info.roleOfOtherCollider << std::endl;
                    transformComponent->moveUp();
                }
                else if (col_info.roleOfOtherCollider == "RightWall")
                {
                    // std::cout << "Role: " << col_info.roleOfOtherCollider << std::endl;
                    transformComponent->moveLeft();
                }
                else if (col_info.roleOfOtherCollider == "paddle")
                {
                    // std::cout << "Role: " << col_info.roleOfOtherCollider << std::endl;
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

