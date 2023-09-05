#pragma once
#include "RectangularGeometry.h"

static const RectangularGeometry WINDOW_SIZE{600, 400};

class Game
{
    Game(RectangularGeometry windowSize = WINDOW_SIZE);

  public:
    bool initialize();
    void handleInput();
    void update();
    void output();
    void destroy();

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

    static Game *getInstance();

  private:
    bool m_running;
    RectangularGeometry m_windowSize;
};
