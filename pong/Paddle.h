#pragma once
#include "GameObject.h"
#include "Interfaces.h"
#include "RectangularShape.h"
#include "components/TransformComponent.h"

class Paddle : public GameObject
{
  public:
    explicit Paddle(IEventManager *, IRenderer *renderer);
};

class ConstrainedTransformComponent : public TransformComponent
{
  public:
    ConstrainedTransformComponent(
        GameObject *owner, ComponentManager *manager, glm::ivec2 initialPosition, RectangularGeometry initialSize,
        std::function<glm::ivec2(std::pair<const glm::ivec2 &, const glm::ivec2 &>)> positionConstraint)
        : TransformComponent(owner, manager, initialPosition, initialSize), m_constraintNewPosition{
                                                                                std::move(positionConstraint)}
    {
    }
    void jump(int y)
    {
        setPosition({position().x, position().y + y});
    }
    void setPosition(glm::ivec2 newPosition)
    {
        m_position = m_constraintNewPosition({m_position, newPosition});
    }

  private:
    std::function<glm::ivec2(std::pair<const glm::ivec2 &, const glm::ivec2 &>)> m_constraintNewPosition;
};

struct PaddleDrawableComponent : DrawableComponent
{
    PaddleDrawableComponent(Paddle *owner, DrawableComponentManagerBase *manager)
        : DrawableComponent{owner, manager}, m_transformComponent{nullptr},
          m_shape(glm::ivec2{100, 100}, RectangularGeometry{20, 100}, glm::u8vec4{200, 200, 100, 255})
    {
        m_drawable = &m_shape;
        m_transformComponent = owner->component<TransformComponent>();
    }

    void update(float deltatime) override
    {
        m_shape.setPosition(m_transformComponent->position());
    }

    void setColor(glm::u8vec4 color)
    {
        m_shape.setColor(color);
    }

  private:
    TransformComponent *m_transformComponent;
    RectangularShape m_shape;
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
            m_owner->component<ConstrainedTransformComponent>()->jump(10);
        }
        Paddle *m_owner;
    };
    PaddleInputComponent(Paddle *owner, ComponentManager *manager_) : InputComponent{owner, manager_}, m_listener{owner}
    {
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
