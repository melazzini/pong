#pragma once
#include "EventManagementInterface.h"
#include "GameObject.h"
#include "SimpleTicker.h"
#include <unordered_set>
#include <vector>

class GameBase
{
  public:
    struct GameBackend
    {
        IWindow *window;
        IRenderer *renderer;
        IEventManager *eventManager;
        ITicker *ticker;
    };

    
    /**
     * @brief Instantiates a GameBase object.
     *
     * @param backend This is the backend that provides all the basic functionalities for the game.
     */
    GameBase(GameBackend *backend);
    bool initialize();
    void handleInput();
    void update();
    void output();
    void destroy();


    /**
     * @brief Adds a GameObject to the game.
     *
     * @param gameObject The GameObject that will be added.
     * @param gameObectTag The tag that identifies this game object.
     *
     * @return true if the GameObject was successfully added, else returns false.
     *
     * @see hasGameObject()
     * @note This method will have an overload that creates the GameObject internally, so that you don't need to do that manually.
     * @code{.cpp}
     * game->addGameObject(std::make_unique<ExampleGameObject>(),"example");
     * @endcode
     */
    bool addGameObject(std::unique_ptr<GameObject> gameObject, std::string gameObectTag);


    /**
     * @brief Check whether or not the game contains the corresponding GameObject instance.
     *
     * @param tag Identifier of the GameObject instance.
     *
     * @return `true` is the game has contains the GameObject, else `false`.
     * @attention At the present, it is not defined yet whether the GameObject 
     *             tag should be unique for each instance contained in the game. 
     * @warning This documentation is just a draft.
     */
    bool hasGameObject(std::string_view tag) const;
    bool hasComponentManager(ComponentManager *manager) const;
    int launch();

    bool loadGameObjects();

    void setRunning(bool trueFalse)
    {
        m_running = trueFalse;
    }

    [[nodiscard]] bool isRunning() const
    {
        return m_running;
    }

    void removeAllManagers()
    {
        m_managers.clear();
    }

    const std::unordered_set<ComponentManager *> managers() const
    {
        return m_managers;
    }

  protected:
    GameBackend *m_backend;

  private:
    bool m_running;
    std::vector<std::pair<std::unique_ptr<GameObject>, std::string>> m_gameObjects;
    std::unordered_set<ComponentManager *> m_managers;
};
