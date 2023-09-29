#include "GameLoop.h"
#include "EventManager.h"
#include "GameInterfaces.h"
#include "components/Component.h"
#include <algorithm>
#include <vector>

void GameLoop::update(uint32_t deltatime, IGameObjectsManager *gameObjectsManager)
{
    gameObjectsManager->updateGameObjects(deltatime);
}

void GameLoop::generateOutput(IGameObjectsManager *gameObjectsManager)
{
    gameObjectsManager->generateOutputFromGameObjects();
}

void GameLoop::destroy(IGameObjectsManager *gameObjectsManager)
{
    gameObjectsManager->destroyAllGameObjects();
}

void GameLoop::handleInput(IEventManager *eventManager)
{
    eventManager->pollEvents();
}
