#pragma once
#include "EventManagementInterface.h"
#include "GameObject.h"
#include "Interfaces.h"
#include <unordered_set>
#include <vector>

class GameBase
{
  public:
    struct GameBackend
    {
        IWindow *window;
        IRenderer *renderer;
        IEventManager *eventManager;
    };

    GameBase(GameBackend *backend);
    bool initialize();
    void handleInput();
    void update();
    void output();
    void destroy();
    bool addGameObject(std::unique_ptr<GameObject> gameObject, std::string gameObectTag);
    bool hasGameObject(std::string_view tag) const;
    bool hasComponentManager(ComponentManager *manager) const;

    bool loadGameObjects();

    void setRunning(bool trueFalse)
    {
        m_running = trueFalse;
    }

    [[nodiscard]] bool isRunning() const
    {
        return m_running;
    }

    void removeAllManagers()
    {
        m_managers.clear();
    }

    const std::unordered_set<ComponentManager *> managers() const
    {
        return m_managers;
    }

  protected:
    GameBackend *m_backend;
    bool m_running;
    std::vector<std::pair<std::unique_ptr<GameObject>, std::string>> m_gameObjects;
    std::unordered_set<ComponentManager *> m_managers;
};
