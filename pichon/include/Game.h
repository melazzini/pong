#pragma once
#include "GameBase.h"
#include "RectangularGeometry.h"

static const RectangularGeometry WINDOW_SIZE{600, 600};

class Game : public GameBase
{
    struct _Pimpl;

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

    int launchGame();

  private:
    Game(GameBackend *backend, RectangularGeometry windowSize = WINDOW_SIZE);
    RectangularGeometry m_windowSize;
    _Pimpl *m_pimpl;
};
