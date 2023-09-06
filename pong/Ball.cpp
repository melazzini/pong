#include "Ball.h"
#include "components/BoxColliderComponent.h"
#include "components/DrawableComponent.h"
#include "components/TransformComponent.h"

Ball::Ball()
{
    auto transform = addComponent<TransformComponent>(this, TransformComponentManager::getInstance());
    transform->setPosition(glm::ivec2{WINDOW_SIZE.width() / 2, WINDOW_SIZE.height() / 2});
    auto drawableComponent{addComponent<RectangularShapeComponent>(this, DrawableComponentManager::getInstance())};
    auto boxColliderComponent{addComponent<BoxColliderComponent>(this, BoxColliderComponentManager::getInstance())};
}

