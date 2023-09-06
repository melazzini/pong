#pragma once
#include "GameObject.h"
#include "RectangularGeometry.h"
#include "components/Component.h"
#include <memory>
#include <string_view>
#include <unordered_set>

static const RectangularGeometry WINDOW_SIZE{600, 400};

class Game
{
  public:
    static Game *getInstance();

  public:
    bool initialize();
    void handleInput();
    void update();
    void output();
    void destroy();

    bool hasGameObject(std::string_view tag) const;

    bool addGameObject(std::unique_ptr<GameObject> gameObject, std::string gameObectTag);

    bool hasComponentManager(ComponentManager *manager) const;

    void setRunning(bool trueFalse)
    {
        m_running = trueFalse;
    }

    [[nodiscard]] bool isRunning() const
    {
        return m_running;
    }

    [[nodiscard]] RectangularGeometry windowSize() const
    {
        return m_windowSize;
    }

    void setWindowSize(RectangularGeometry newSize)
    {
        m_windowSize = newSize;
    }

    bool loadGameObjects();

    const std::unordered_set<ComponentManager *> managers() const
    {
        return m_managers;
    }

    void removeAllManagers()
    {
        m_managers.clear();
    }

  private:
    Game(RectangularGeometry windowSize = WINDOW_SIZE);

    bool m_running;
    RectangularGeometry m_windowSize;
    std::vector<std::pair<std::unique_ptr<GameObject>, std::string>> m_gameObjects;
    std::unordered_set<ComponentManager *> m_managers;
};
