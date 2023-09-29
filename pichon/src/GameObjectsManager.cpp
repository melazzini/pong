#include "GameObjectsManager.h"
#include "GameObject.h"

bool GameObjectsManager::addGameObject(std::unique_ptr<GameObject> gameObject, const std::string &tag)
{
    if (gameObject == nullptr || m_gameObjects.contains(tag))
    {
        return false;
    }
    m_gameObjects[tag] = std::move(gameObject);
    return true;
}

bool GameObjectsManager::removeGameObject(const std::string &tag)
{
    if (m_gameObjects.contains(tag))
    {
        m_gameObjects.erase(tag);
        return true;
    }
    return false;
}

bool GameObjectsManager::hasGameObject(const std::string &tag) const
{
    if (m_gameObjects.contains(tag))
    {
        return true;
    }
    return false;
}

void GameObjectsManager::updateGameObjects(uint32_t deltatime)
{
}

void GameObjectsManager::generateOutputFromGameObjects()
{
}

void GameObjectsManager::destroyAllGameObjects()
{
}
