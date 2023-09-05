#include "Ball.h"

Ball::Ball()
{
    TransformComponentManager transformComponentManager;
    DrawableComponentManager drawableComponentManager;
    BoxColliderComponentManager boxColliderComponentManager;

    auto transform = addComponent<TransformComponent>(this, &transformComponentManager);
    transform->setPosition(glm::ivec2{WINDOW_SIZE.width() / 2, WINDOW_SIZE.height() / 2});
    auto drawableComponent{addComponent<RectangularShapeComponent>(this, &drawableComponentManager)};
    auto boxColliderComponent{addComponent<BoxColliderComponent>(this, &boxColliderComponentManager)};
}

