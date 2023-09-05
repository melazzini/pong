#include "Paddle.h"
#include "Game.h"
#include "components.h"
#include <memory>

Paddle::Paddle()
{
    const RectangularGeometry size{20, 100};
    auto transformComponent = addComponent<ConstrainedTransformComponent>(
        glm::ivec2{size.width() / 2, WINDOW_SIZE.height() / 2}, size, [](auto oldNewPair) {
            return glm::ivec2{oldNewPair.first.x, oldNewPair.second.y};
        });

    auto drawableComponent{addComponent<RectangularShapeComponent>()};
    auto inputComponent{addComponent<InputComponent>()};
    auto boxColliderComponent{addComponent<BoxColliderComponent>()};
}
