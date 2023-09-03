#include "Paddle.h"
#include "Game.h"
#include "TransformComponent.h"
#include <memory>

Paddle::Paddle()
{
    const RectangularGeometry size{20, 100};
    auto transformComponent = addComponent<ConstraintTransformComponent>(
        glm::ivec2{size.width() / 2, WINDOW_SIZE.height() / 2}, size, [](auto oldNewPair) {
            return glm::ivec2{oldNewPair.first.x, oldNewPair.second.y};
        });
}
