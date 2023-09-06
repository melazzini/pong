#pragma once
#include "EventManagementInterface.h"
#include "GameBase.h"
#include "RectangularGeometry.h"

static const RectangularGeometry WINDOW_SIZE{600, 400};

class Game : public GameBase
{
  public:
    static Game *getInstance(GameBackend *backend);

    [[nodiscard]] RectangularGeometry windowSize() const
    {
        return m_windowSize;
    }

    void setWindowSize(RectangularGeometry newSize)
    {
        m_windowSize = newSize;
    }

  private:
    Game(GameBackend *backend, RectangularGeometry windowSize = WINDOW_SIZE);
    RectangularGeometry m_windowSize;
};
