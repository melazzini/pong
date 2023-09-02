#include "Game.h"
#include "Paddle.h"
#include "TransformComponent.h"
#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using testing::Eq;
using testing::Ne;

Paddle::Paddle() : m_transform{std::make_unique<TransformComponent>()}
{
    m_transform->setPosition(glm::ivec2{m_transform->size().width() / 2, WINDOW_SIZE.height() / 2});
}

TEST(ThePaddle, StartsCenteredOnTheLeftOfTheScreen)
{
    Game game{};
    Paddle paddle{};
    ASSERT_THAT(paddle.component<TransformComponent>().position().x,
                Eq(paddle.component<TransformComponent>().size().width() / 2));
    ASSERT_THAT(paddle.component<TransformComponent>().position().y, Eq(game.windowSize().height() / 2));
}

TEST(ThePaddle, CanChangeItsPosition)
{
    Paddle paddle{};

    ASSERT_THAT(paddle.component<TransformComponent>().position(), Ne(glm::ivec2{10, 100}));
    paddle.component<TransformComponent>().setPosition(glm::ivec2{10, 100});
    ASSERT_THAT(paddle.component<TransformComponent>().position(), Eq(glm::ivec2{10, 100}));
}
