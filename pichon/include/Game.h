#pragma once
#include "GameObject.h"
#include "RectangularGeometry.h"
#include <memory>
#include <string_view>

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

  private:
    Game(RectangularGeometry windowSize = WINDOW_SIZE);

    bool m_running;
    RectangularGeometry m_windowSize;
    std::vector<std::pair<std::unique_ptr<GameObject>, std::string>> m_gameObjects;
};
