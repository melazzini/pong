#pragma once
#include "EventManagementInterface.h"
#include "GameObject.h"
#include "Interfaces.h"
#include "RectangularGeometry.h"
#include "components/Component.h"
#include <memory>
#include <string_view>
#include <unordered_set>

static const RectangularGeometry WINDOW_SIZE{600, 400};

class GameBase
{
  public:
    struct GameBackend
    {
        IWindow *window;
        IRenderer *renderer;
        IEventManager *eventManager;
    };
    GameBase(GameBackend *backend) : m_backend(backend), m_running(false)
    {
    }
    bool initialize();
    void handleInput();
    void update();
    void output();
    void destroy();

    bool loadGameObjects();

    void setRunning(bool trueFalse)
    {
        m_running = trueFalse;
    }

    [[nodiscard]] bool isRunning() const
    {
        return m_running;
    }

  protected:
    GameBackend *m_backend;
    bool m_running;
};

class Game : public GameBase
{
  public:
    static Game *getInstance(GameBackend *backend);

  public:
    bool hasGameObject(std::string_view tag) const;

    bool addGameObject(std::unique_ptr<GameObject> gameObject, std::string gameObectTag);

    bool hasComponentManager(ComponentManager *manager) const;

    [[nodiscard]] RectangularGeometry windowSize() const
    {
        return m_windowSize;
    }

    void setWindowSize(RectangularGeometry newSize)
    {
        m_windowSize = newSize;
    }

    const std::unordered_set<ComponentManager *> managers() const
    {
        return m_managers;
    }

    void removeAllManagers()
    {
        m_managers.clear();
    }

  private:
    Game(GameBackend *backend, RectangularGeometry windowSize = WINDOW_SIZE);
    RectangularGeometry m_windowSize;
    std::vector<std::pair<std::unique_ptr<GameObject>, std::string>> m_gameObjects;
    std::unordered_set<ComponentManager *> m_managers;
};
