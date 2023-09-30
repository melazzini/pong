#pragma once
#include "EventUtils.h"
#include "Events.h"
#include "GameObject.h"
#include "Interfaces.h"
#include "RectangularColliderComponentManager.h"
#include "RectangularShape.h"
#include "components/TransformComponent.h"
#include "utils.h"
#include <memory>
#include <type_traits>

class Paddle : public GameObject
{
  public:
    explicit Paddle(IEventManager *, IRenderer *renderer);
};

// A transformComponent is the component that you update
// from the outside of the gameobject, for example
// from the user input or an ai system.
//
// Other components will consume the information provided
// by this component in order to do their things(eg drawing)
class ConstrainedTransformComponent : public TransformComponent
{
  public:
    ConstrainedTransformComponent(
        GameObject *owner, IComponentManager *manager, glm::ivec2 initialPosition, RectangularGeometry initialSize,
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

// In this component you simply do all the drawing that you need
// inside the update(deltatime) method, normally you will need
// to query the transformComponent to get position and size info
// about the gameobject
//
// This class should store the drawable that will be used
// by the gameobject (simple-drawable, animated drawable etc).
struct PaddleDrawableComponent : DrawableComponent
{
    PaddleDrawableComponent(Paddle *owner, DrawableComponentManagerBase *manager)
        : DrawableComponent{owner, manager}, m_transformComponent{nullptr},
          m_shape(glm::ivec2{100, 100}, RectangularGeometry{20, 100}, glm::u8vec4{200, 200, 100, 255})
    {
        m_drawable = &m_shape;
        m_transformComponent = owner->component<TransformComponent>();
    }

    void update(uint32_t deltatime) override
    {
        m_shape.setPosition(m_transformComponent->position());
        m_shape.setWidth(m_transformComponent->size().width());
        m_shape.setHeight(m_transformComponent->size().height());
    }

    void setColor(glm::u8vec4 color)
    {
        m_shape.setColor(color);
    }

  private:
    TransformComponent *m_transformComponent;
    RectangularShape m_shape;
};

// This class is in charge of handling input, thus
// it should have a ref to the input component manager,
// which will provide the input-reading capabilities,
// and it also probably uses a listener to listen for
// events.
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

            auto &evt{dynamic_cast<const ArrowKeyPressed &>(event)};
            if (evt.key() == ArrowKey::UP)
            {
                m_owner->component<ConstrainedTransformComponent>()->jump(-10);
            }
            else if (evt.key() == ArrowKey::DOWN)
            {
                m_owner->component<ConstrainedTransformComponent>()->jump(10);
            }
        }
        Paddle *m_owner;
    };

    PaddleInputComponent(Paddle *owner, IComponentManager *manager_)
        : InputComponent{owner, manager_}, m_listener{owner}
    {
        m_inputManager = dynamic_cast<InputComponentManagerBase *>(manager());
        //        m_inputManager->registerListener(&m_listener);
        m_owner = dynamic_cast<Paddle *>(owner);
    }
    void update(uint32_t deltatime) override
    {
        if (m_inputManager->isKeyPressed(Keyboard::UP))
        {
            m_owner->component<ConstrainedTransformComponent>()->jump(-8);
        }
        else if (m_inputManager->isKeyPressed(Keyboard::DOWN))
        {
            m_owner->component<ConstrainedTransformComponent>()->jump(8);
        }
    }

  private:
    InputComponentManagerBase *m_inputManager;
    KeyBoardEventListener m_listener;
    Paddle *m_owner;
};
