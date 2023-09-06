#include "Paddle.h"
#include "Game.h"
#include "components.h"
#include "components/BoxColliderComponent.h"
#include "components/DrawableComponent.h"
#include "components/InputComponent.h"
#include "components/TransformComponent.h"
#include <memory>

Paddle::Paddle()
{
    const RectangularGeometry size{20, 100};
    auto transformComponent = addComponent<ConstrainedTransformComponent>(
        this, TransformComponentManager::getInstance(), glm::ivec2{size.width() / 2, WINDOW_SIZE.height() / 2}, size,
        [](auto oldNewPair) {
            return glm::ivec2{oldNewPair.first.x, oldNewPair.second.y};
        });

    auto drawableComponent{addComponent<RectangularShapeComponent>(this, DrawableComponentManager::getInstance())};
    auto inputComponent{addComponent<InputComponent>(this, InputComponentManager::getInstance())};
    auto boxColliderComponent{addComponent<BoxColliderComponent>(this, BoxColliderComponentManager::getInstance())};
}
