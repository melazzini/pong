#include "GameObjectsManager.h"
#include "GameObject.h"
#include "components/Component.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

bool GameObjectsManager::addGameObject(std::unique_ptr<GameObject> gameObject, const std::string &tag)
{
    if (insertionIsValid(gameObject.get(), tag))
    {
        extractComponentManagersAndRegisterTheirComponents(gameObject->componentList());
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
    std::for_each(std::begin(m_componentManagers), std::end(m_componentManagers),
                  [deltatime](IComponentManager *componentManager) { componentManager->updateComponents(deltatime); });
}

void GameObjectsManager::generateOutputFromGameObjects()
{
    std::for_each(std::begin(m_outputComponentManagers), std::end(m_outputComponentManagers),
                  [](IOutputComponentManager *outputComonentManager) { outputComonentManager->output(); });
}

void GameObjectsManager::destroyAllGameObjects()
{
    std::for_each(std::begin(m_componentManagers), std::end(m_componentManagers),
                  [](IComponentManager *componentManager) { componentManager->destroyComponents(); });
}

bool GameObjectsManager::insertionIsValid(GameObject *object, const std::string &tag) const
{
    return (object != nullptr) && !m_gameObjects.contains(tag);
}
void GameObjectsManager::extractComponentManagersAndRegisterTheirComponents(
    const std::vector<std::unique_ptr<IComponent>> &componentList)
{
    std::for_each(std::cbegin(componentList), std::cend(componentList),
                  [this](const std::unique_ptr<IComponent> &component) {
                      auto manager_{component->manager()};
                      validateComponentManager(manager_);
                      if (!isComponentManagerADuplicateOfAnExistingOne(manager_))
                      {
                          registerComponentManager(manager_);
                      }
                      registerComponent(manager_, component.get());
                  });
}

bool GameObjectsManager::hasComponentManager(IComponentManager *manager) const
{
    return m_componentManagers.contains(manager);
}

bool GameObjectsManager::hasOutputComponentManager(IOutputComponentManager *outputComonentManager) const
{
    return m_outputComponentManagers.contains(outputComonentManager);
}
const std::unordered_set<IComponentManager *> &GameObjectsManager::listOfComponentManagers() const
{
    return m_componentManagers;
}

void GameObjectsManager::validateComponentManager(IComponentManager *componentManager) const
{
    if (componentManager == nullptr)
    {
        throw std::runtime_error{
            "Attempt to provide a GameObject, which has a component with a null ComponentManager!"};
    }
}

bool GameObjectsManager::isComponentManagerADuplicateOfAnExistingOne(IComponentManager *manager_) const
{
    return m_componentManagers.contains(manager_);
}

void GameObjectsManager::registerComponentManager(IComponentManager *componentManager)
{
    m_componentManagers.emplace(componentManager);
    if (auto outputComponentManager{dynamic_cast<IOutputComponentManager *>(componentManager)}; outputComponentManager)
    {
        m_outputComponentManagers.emplace(outputComponentManager);
    }
}
void GameObjectsManager::registerComponent(IComponentManager *componentManager, IComponent *component)
{
    componentManager->registerComponent(component);
}
