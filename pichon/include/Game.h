#pragma once
#include "EventManagementInterface.h"
#include "Interfaces.h"
#include "RectangularGeometry.h"

static const RectangularGeometry WINDOW_SIZE{600, 600};
struct GameObject;
class Game
{
    struct _Pimpl;

  public:
    struct GameBackend
    {
        IWindow *window;
        IRenderer *renderer;
        IEventManager *eventManager;
        ITicker *ticker;
    };
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

    bool addGameObject(std::unique_ptr<GameObject> gameobj, const std::string &tag);

    void terminate();

  private:
    Game(GameBackend *backend, RectangularGeometry windowSize = WINDOW_SIZE);
    RectangularGeometry m_windowSize;
    GameBackend *m_backend;
    _Pimpl *m_pimpl;
};
