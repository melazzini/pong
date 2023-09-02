#pragma once
#include "RectangularGeometry.h"

class Game
{
  public:
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
        return RectangularGeometry{0, 0};
    }

  private:
    bool m_running;
};
