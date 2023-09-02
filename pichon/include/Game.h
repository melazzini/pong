#pragma once
#include "RectangularGeometry.h"

class Game
{
  public:
    Game(RectangularGeometry windowSize = RectangularGeometry{}) : m_running{false}, m_windowSize{windowSize}
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
