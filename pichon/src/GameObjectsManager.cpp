#include "GameObjectsManager.h"
#include "GameObject.h"

bool GameObjectsManager::addGameObject(std::unique_ptr<GameObject> gameObject, const std::string &tag)
{
    if (insertionIsValid(gameObject.get(), tag))
    {
        m_gameObjects[tag] = std::move(gameObject);
        return true;
    }
    return false;
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
    return m_gameObjects.contains(tag);
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

bool GameObjectsManager::insertionIsValid(GameObject *object, const std::string &tag) const
{
    return (object != nullptr) && !m_gameObjects.contains(tag);
}
