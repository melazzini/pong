#include "Paddle.h"
#include "Game.h"
#include "TransformComponent.h"

Paddle::Paddle() : m_transform{std::make_unique<TransformComponent>()}
{
    m_transform->setPosition(glm::ivec2{m_transform->size().width() / 2, WINDOW_SIZE.height() / 2});
}
