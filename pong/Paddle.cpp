#include "Paddle.h"
#include "Game.h"
#include "components.h"
#include "components/TransformComponent.h"
#include <memory>

Paddle::Paddle()
{
    DrawableComponentManager drawableComponentManager;
    InputComponentManager inputComponentManager;
    BoxColliderComponentManager boxColliderComponentManager;

    const RectangularGeometry size{20, 100};
    auto transformComponent = addComponent<ConstrainedTransformComponent>(
        this, TransformComponentManager::getInstance(), glm::ivec2{size.width() / 2, WINDOW_SIZE.height() / 2}, size,
        [](auto oldNewPair) {
            return glm::ivec2{oldNewPair.first.x, oldNewPair.second.y};
        });

    auto drawableComponent{addComponent<RectangularShapeComponent>(this, &drawableComponentManager)};
    auto inputComponent{addComponent<InputComponent>(this, &inputComponentManager)};
    auto boxColliderComponent{addComponent<BoxColliderComponent>(this, &boxColliderComponentManager)};
}
