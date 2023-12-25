#pragma once
#include "GameInterfaces.h"
#include <memory>
#include <unordered_map>
#include <unordered_set>

struct IComponent;
struct IComponentManager;
struct IOutputComponentManager;

class GameObjectsManager : public IGameObjectsManager
{
  public:
    bool addGameObject(std::unique_ptr<GameObject> gameObject, const std::string &tag) override;
    bool removeGameObject(const std::string &tag) override;
    bool hasGameObject(const std::string &tag) const override;
    void updateGameObjects(uint32_t deltatime) override;
    void generateOutputFromGameObjects() override;
    void destroyAllGameObjects() override;
    bool hasComponentManager(IComponentManager *manager) const override;
    bool hasOutputComponentManager(IOutputComponentManager *outputComonentManager) const override;
    const std::unordered_set<IComponentManager *> &listOfComponentManagers() const override;

  private:
    std::unordered_map<std::string, std::unique_ptr<GameObject>> m_gameObjects;
    std::unordered_set<IComponentManager *> m_componentManagers;
    std::unordered_set<IOutputComponentManager *> m_outputComponentManagers;

  private:
    bool insertionIsValid(GameObject *object, const std::string &tag) const;
    void extractComponentManagersAndRegisterTheirComponents(
        const std::vector<std::unique_ptr<IComponent>> &componentList);
    void validateComponentManager(IComponentManager *componentManager) const;
    bool isComponentManagerADuplicateOfAnExistingOne(IComponentManager *componentManager) const;
    void registerComponentManager(IComponentManager *componentManager);
    void registerComponent(IComponentManager *componentManager, IComponent *component);
    void registerComponentManagerIfNotDuplicated(IComponentManager *componentManager);
};
