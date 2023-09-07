#include "Paddle.h"
#include "EventManagementInterface.h"
#include "EventUtils.h"
#include "Game.h"
#include "GameObject.h"
#include "Interfaces.h"
#include "components.h"
#include "components/BoxColliderComponent.h"
#include "components/Component.h"
#include "components/DrawableComponent.h"
#include "components/InputComponent.h"
#include "components/TransformComponent.h"
#include <glm/fwd.hpp>
#include <memory>

struct PaddleShape : Box
{
    PaddleShape(glm::ivec2 position, int size)
        : Box(position, RectangularGeometry{size, size}, std::make_unique<BoxDrawablePrimitiveSDL>()),
          m_boxDrawablePrimitive(dynamic_cast<BoxDrawablePrimitiveSDL *>(m_primitive.get()))
    {
    }

    void draw() override
    {
        std::cout << "drawing ..." << std::endl;
        m_boxDrawablePrimitive->position = position();
        m_boxDrawablePrimitive->size = {width(), height()};
        m_boxDrawablePrimitive->color = m_color;
    }

    void setColor(glm::u8vec4 color)
    {
        m_color = color;
    }

  private:
    BoxDrawablePrimitiveSDL *m_boxDrawablePrimitive;
    glm::u8vec4 m_color{255, 0, 0, 255};
};

struct PaddleDrawableComponent : DrawableComponent
{
    PaddleDrawableComponent(Paddle *owner, DrawableComponentManagerBase *manager)
        : DrawableComponent{owner, manager}, m_owner{owner}, m_manager(manager), m_shape(glm::ivec2{100, 100}, 60)
    {
        m_drawable = &m_shape;
    }

    void update(float deltatime) override
    {
    }

    void jump(int y)
    {
        m_shape.setPosition({m_shape.position().x, m_shape.position().y + y});
    }

    void setColor(glm::u8vec4 color)
    {
        m_shape.setColor(color);
    }

  private:
    Paddle *m_owner;
    DrawableComponentManagerBase *m_manager;
    PaddleShape m_shape;
};

struct PaddleInputComponent : InputComponent
{
    struct KeyBoardEventListener : IListener
    {
        KeyBoardEventListener(Paddle *owner) : m_owner(owner)
        {
        }
        EventType eventType() const override
        {
            return EventType::ARROW_KEYS_PRESSED;
        }
        void onEvent(const IEvent &event) override
        {
            std::cout << "Great!!!" << std::endl;
            m_owner->component<PaddleDrawableComponent>()->jump(10);
        }
        Paddle *m_owner;
    };
    PaddleInputComponent(Paddle *owner, ComponentManager *manager_) : InputComponent{owner, manager_}, m_listener{owner}
    {
        /*
         *manager->registerListener(eventtype,[](){})
         */
        m_inputManager = dynamic_cast<InputComponentManagerBase *>(manager());
        m_inputManager->registerListener(&m_listener);
        m_owner = dynamic_cast<Paddle *>(owner);
    }
    void update(float deltatime) override
    {
        if (m_inputManager->isKeyPressed(Keyboard::A))
        {
            std::cout << "Yes SR!" << std::endl;
            m_owner->component<PaddleDrawableComponent>()->setColor(glm::u8vec4{100, 100, 255, 255});
        }
    }

  private:
    InputComponentManagerBase *m_inputManager;
    KeyBoardEventListener m_listener;
    Paddle *m_owner;
};

Paddle::Paddle(IEventManager *eventManager, IRenderer *renderer)
{
    const RectangularGeometry size{20, 100};
    auto transformComponent = addComponent<ConstrainedTransformComponent>(
        this, TransformComponentManager::getInstance(), glm::ivec2{size.width() / 2, WINDOW_SIZE.height() / 2}, size,
        [](auto oldNewPair) {
            return glm::ivec2{oldNewPair.first.x, oldNewPair.second.y};
        });

    auto drawableComponent{
        addComponent<PaddleDrawableComponent>(this, DrawableComponentManager::getInstance(renderer))};
    auto inputComponent{addComponent<PaddleInputComponent>(this, InputComponentManager::getInstance(eventManager))};
    auto boxColliderComponent{addComponent<BoxColliderComponent>(this, BoxColliderComponentManager::getInstance())};
}
