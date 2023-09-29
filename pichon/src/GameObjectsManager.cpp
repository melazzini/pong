#include "GameObjectsManager.h"
#include "GameObject.h"
#include "components/Component.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

bool GameObjectsManager::addGameObject(std::unique_ptr<GameObject> gameObject, const std::string &tag)
{
    if (insertionIsValid(gameObject.get(), tag))
    {
        extractComponentManagers(gameObject->componentList());
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
void GameObjectsManager::extractComponentManagers(const std::vector<std::unique_ptr<IComponent>> &componentList)
{
    std::for_each(std::cbegin(componentList), std::cend(componentList),
                  [this](const std::unique_ptr<IComponent> &component) {
                      auto manager_{component->manager()};
                      if (!m_componentManagers.contains(manager_))
                      {
                          m_componentManagers.emplace(manager_);
                      }
                  });
}

bool GameObjectsManager::hasComponentManager(ComponentManager *manager) const
{
    return m_componentManagers.contains(manager);
}

const std::unordered_set<ComponentManager *> &GameObjectsManager::listOfComponentManagers() const
{
    return m_componentManagers;
}
