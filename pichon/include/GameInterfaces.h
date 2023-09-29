#pragma once
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

struct GameObject;
struct ComponentManager;
struct OutputComponentManager;
struct IGameObjectsManager;
struct IEventManager;

/**
 * @brief This is the interface of a game loop.
 */
struct IGameLoop
{
    virtual ~IGameLoop() = default;

    /**
     * @brief This method initializes the game.
     *
     * This method should be used to finish the initialization of game.
     * Anything, that for some reason, cannot be initialized in the game ctor,
     * should be initialized in this method.
     *
     * @return `true` is the initialization succeeded, else `false`.
     */
    [[nodiscard]] virtual bool initialize() = 0;

    /**
     * @brief This is where game should handle user or Operating System's events.
     *
     * For example, network messages or data comming from the network,
     * or user keyboard events that are important to the game like presing ESCAPE
     * to quit the game, etc, all of this should be handle inside this method.
     *
     * @param eventManager The manager of events in the game.
     */
    virtual void handleInput(IEventManager *eventManager) = 0;

    /**
     * @brief In this method the game should update its state.
     *
     * For example, the game should update here the game objects.
     * In general, in this method the game should update anything that
     * has to be updated each game frame.
     *
     * @param deltatime The amount of time in milliseconds, counted since the last frame.
     * @param gameObjectsManager The manager of the game objects in the game.
     */
    virtual void update(uint32_t deltatime, IGameObjectsManager *gameObjectsManager) = 0;

    /**
     * @brief This method outputs any content, like audio and game graphics.
     *
     * For example, here is where the game should draw its graphics.
     *
     * @param gameObjectsManager The manager of the game objects in the game.
     *
     * @note This is not where the game updates drawables, or any other component
     *       that produces graphics, for that task you the game should use update().
     */
    virtual void generateOutput(IGameObjectsManager *gameObjectsManager) = 0;

    /**
     * @brief Here the game internal state gets destroyed.
     *
     * Here the game should clean up all the resources it uses and it owns, destroy all the remaining
     * components, and any other dependencies that it owns should also be destroyed here.
     *
     * @param gameObjectsManager The manager of the game objects in the game.
     */
    virtual void destroy(IGameObjectsManager *gameObjectsManager) = 0;
};

/**
 * @brief This is the interface of game objects manager.
 *
 * The role of an IGameObjectsManager is to provide methods to manage
 * the game objects lifecycle using the component managers.
 */
struct IGameObjectsManager
{
    virtual ~IGameObjectsManager() = default;

    /**
     * @brief This method adds a new game object with a unique tag.
     *
     * @param gameObject The new game object to be added.
     * @param gameObectTag The game object's unique tag.
     *
     * @return `true` if the game object was added successfully, else `false`.
     */
    virtual bool addGameObject(std::unique_ptr<GameObject> gameObject, const std::string &gameObectTag) = 0;

    /**
     * @brief This method removes a contained game object.
     *
     * Because the game objects manager should own the game objects,
     * this method should destroy the game object that will be removed.
     *
     * @param gameObectTag Tag of the game object to be removed.
     *
     * @return `true` if the game object was successfully removed.
     */
    virtual bool removeGameObject(const std::string &gameObectTag) = 0;

    /**
     * @brief This checks if the game manager contains the game object with the given tag.
     *
     * @param tag Tag of the game object.
     *
     * @return `true` if the manager contains the given game object, else `false`.
     */
    virtual bool hasGameObject(const std::string &tag) const = 0;

    /**
     * @brief This method should update the game objects in the game.
     *
     * @param deltatime The deltatime since last frame of the game.
     */
    virtual void updateGameObjects(uint32_t deltatime) = 0;

    /**
     * @brief This method makes the game objects that generate output
     * to do it.
     */
    virtual void generateOutputFromGameObjects() = 0;

    /**
     * @brief This method destroys all the game objects.
     */
    virtual void destroyAllGameObjects() = 0;

    /**
     * @brief Checks if the given component manager is listed in and used by the GameObjectsManager.
     *
     * @param manager The corresponding component manager.
     *
     * @return  `true` if the manager is in the list of ComponentManager s, else `false`
     */
    virtual bool hasComponentManager(ComponentManager *manager) const = 0;

    /**
     * @brief This method returns a list of the component managers.
     *
     * @return A list of the component managers.
     *
     * @note This method is mainly for unit-testing and/or inspection purposes.
     */
    virtual const std::unordered_set<ComponentManager *> &listOfComponentManagers() const = 0;
};
