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

Paddle::Paddle(IEventManager *eventManager, IRenderer *renderer)
{
    const RectangularGeometry size{20, 100};
    auto transformComponent = addComponent<ConstrainedTransformComponent>(
        this, TransformComponentManager::getInstance(), glm::ivec2{size.width() / 2, 100}, size, [](auto oldNewPair) {
            if (oldNewPair.second.y > 780 || oldNewPair.second.y < 20)
            {
                return oldNewPair.first;
            }
            return glm::ivec2{oldNewPair.first.x, oldNewPair.second.y};
        });

    auto drawableComponent{
        addComponent<PaddleDrawableComponent>(this, DrawableComponentManager::getInstance(renderer))};
    auto inputComponent{addComponent<PaddleInputComponent>(this, InputComponentManager::getInstance(eventManager))};

    auto ll{addComponent<MyRectangularCollider>(
        RectangularColliderDescriptor{std::make_unique<Boxcollidershape>(), "paddle"}, this,
        RectangularColliderComponentManager::getInstance())};
}
