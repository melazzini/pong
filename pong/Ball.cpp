#include "Ball.h"
#include "Interfaces.h"
#include "components/BoxColliderComponent.h"
#include "components/DrawableComponent.h"
#include "components/TransformComponent.h"

Ball::Ball(IRenderer *renderer)
{
    auto transform = addComponent<TransformComponent>(this, TransformComponentManager::getInstance());
    transform->setPosition(glm::ivec2{WINDOW_SIZE.width() / 2, WINDOW_SIZE.height() / 2});
    auto drawableComponent{addComponent<BallDrawableComponent>(this, DrawableComponentManager::getInstance(renderer))};
    auto boxColliderComponent{addComponent<BoxColliderComponent>(this, BoxColliderComponentManager::getInstance())};
}

