#include "Paddle.h"
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
    PaddleInputComponent(GameObject *owner, ComponentManager *manager) : InputComponent{owner, manager}
    {
        /*
         *manager->registerListener(eventtype,[](){})
         */
        // dynamic_cast<InputComponentManagerBase *>(manager);
    }
    void update(float deltatime) override
    {
        std::cout << "Paddle's InputComponent: " << __FUNCTION__ << std::endl;
        /*
         *manager->isKeyPressed(up);
         */
    }
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
