#include "Ball.h"

Ball::Ball()
{
    auto transform = addComponent<TransformComponent>();
    transform->setPosition(glm::ivec2{WINDOW_SIZE.width() / 2, WINDOW_SIZE.height() / 2});
    auto drawableComponent{addComponent<RectangularShapeComponent>()};
    auto boxColliderComponent{addComponent<BoxColliderComponent>()};
}

