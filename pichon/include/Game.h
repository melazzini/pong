#pragma once
#include "RectangularGeometry.h"

static const RectangularGeometry WINDOW_SIZE{600, 400};

class Game
{
  public:
    Game(RectangularGeometry windowSize = WINDOW_SIZE) : m_running{false}, m_windowSize{windowSize}
    {
    }
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

  private:
    bool m_running;
    RectangularGeometry m_windowSize;
};