#include "Paddle.h"
#include "EventManagementInterface.h"
#include "EventUtils.h"
#include "Game.h"
#include "Interfaces.h"
#include "RectangularColliderComponentManager.h"
#include "components.h"
#include "components/BoxColliderComponent.h"
#include "components/Component.h"
#include "components/DrawableComponent.h"
#include "components/InputComponent.h"
#include "components/TransformComponent.h"
#include <glm/fwd.hpp>
#include <memory>

struct MyRectangularCollider : RectangularColliderComponent
{
    MyRectangularCollider(RectangularColliderDescriptor descriptor, GameObject *owner,
                          RectangularColliderComponentManager *manager_)
        : RectangularColliderComponent(std::move(descriptor), owner, manager_)
    {
        manager_->insertCollisionInfo(RectangularColliderCollisionInfo{"paddle", this, "ball"});
    }
};

class PaddleBoxCollider : public BoxColliderComponent
{
  public:
    PaddleBoxCollider(Paddle *owner, BoxColliderComponentManager *manager)
        : BoxColliderComponent(owner, manager, "paddle")
    {
    }

    void update(float deltatime) override
    {
        std::cout << "PaddleBoxCollider: " << __FUNCTION__ << std::endl;
        // m_manager->checkCollisionWith("tag");
    }
};

Paddle::Paddle(IEventManager *eventManager, IRenderer *renderer)
{
    const RectangularGeometry size{20, 100};
    auto transformComponent = addComponent<ConstrainedTransformComponent>(
        this, TransformComponentManager::getInstance(), glm::ivec2{size.width() / 2, WINDOW_SIZE.height() / 2}, size,
        [](auto oldNewPair) {
            if (oldNewPair.second.y > 300 || oldNewPair.second.y < 0)
            {
                return oldNewPair.first;
            }
            return glm::ivec2{oldNewPair.first.x, oldNewPair.second.y};
        });

    auto drawableComponent{
        addComponent<PaddleDrawableComponent>(this, DrawableComponentManager::getInstance(renderer))};
    auto inputComponent{addComponent<PaddleInputComponent>(this, InputComponentManager::getInstance(eventManager))};

    auto ll{addComponent<MyRectangularCollider>(
        RectangularColliderDescriptor{std::make_unique<Boxcollidershape>(), "paddleRole"}, this,
        RectangularColliderComponentManager::getInstance())};
}
