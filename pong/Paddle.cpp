#include "Paddle.h"
#include "EventManagementInterface.h"
#include "EventUtils.h"
#include "Game.h"
#include "GameObject.h"
#include "components.h"
#include "components/BoxColliderComponent.h"
#include "components/DrawableComponent.h"
#include "components/InputComponent.h"
#include "components/TransformComponent.h"
#include <memory>

struct PaddleInputComponent : InputComponent
{
    struct KeyBoardEventListener : IListener
    {
        EventType eventType() const override
        {
            return EventType::ARROW_KEYS_PRESSED;
        }
        void onEvent(const IEvent &event) override
        {
            std::cout << "Great!!!" << std::endl;
        }
    };
    PaddleInputComponent(GameObject *owner, ComponentManager *manager_) : InputComponent{owner, manager_}
    {
        /*
         *manager->registerListener(eventtype,[](){})
         */
        m_inputManager = dynamic_cast<InputComponentManagerBase *>(manager());
        m_inputManager->registerListener(&m_listener);
    }
    void update(float deltatime) override
    {
    }

  private:
    InputComponentManagerBase *m_inputManager;
    KeyBoardEventListener m_listener;
};

Paddle::Paddle(IEventManager *eventManager)
{
    const RectangularGeometry size{20, 100};
    auto transformComponent = addComponent<ConstrainedTransformComponent>(
        this, TransformComponentManager::getInstance(), glm::ivec2{size.width() / 2, WINDOW_SIZE.height() / 2}, size,
        [](auto oldNewPair) {
            return glm::ivec2{oldNewPair.first.x, oldNewPair.second.y};
        });

    auto drawableComponent{addComponent<RectangularShapeComponent>(this, DrawableComponentManager::getInstance())};
    auto inputComponent{addComponent<PaddleInputComponent>(this, InputComponentManager::getInstance(eventManager))};
    auto boxColliderComponent{addComponent<BoxColliderComponent>(this, BoxColliderComponentManager::getInstance())};
}
