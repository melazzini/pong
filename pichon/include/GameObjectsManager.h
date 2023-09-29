#pragma once
#include "GameInterfaces.h"
#include <memory>
#include <unordered_map>

class GameObjectsManager : public IGameObjectsManager
{
  public:
    bool addGameObject(std::unique_ptr<GameObject> gameObject, const std::string &tag) override;
    bool removeGameObject(const std::string &tag) override;
    bool hasGameObject(const std::string &tag) const override;
    void updateGameObjects(uint32_t deltatime) override;
    void generateOutputFromGameObjects() override;
    void destroyAllGameObjects() override;

  private:
    std::unordered_map<std::string, std::unique_ptr<GameObject>> m_gameObjects;
};
