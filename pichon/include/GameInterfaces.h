#pragma once
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

struct GameObject;
struct ComponentManager;
struct OutputComponentManager;

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
     */
    virtual void handleInput() = 0;

    /**
     * @brief In this method the game should update its state.
     *
     * For example, the game should update here the game objects.
     * In general, in this method the game should update anything that
     * has to be updated each game frame.
     *
     * @param deltatime The amount of time in milliseconds, counted since the last frame.
     * @managers The list of component managers.
     */
    virtual void update(uint32_t deltatime, const std::vector<ComponentManager *> &managers) = 0;

    /**
     * @brief This method outputs any content, like audio and game graphics.
     *
     * For example, here is where the game should draw its graphics.
     *
     * @param outputComponentManagers These are the managers of components that produce any kind of output.
     *
     * @note This is not where the game updates drawables, or any other component
     *       that produces graphics, for that task you the game should use update().
     */
    virtual void output(const std::vector<OutputComponentManager *> &outputComponentManagers) = 0;

    /**
     * @brief Here the game internal state gets destroyed.
     *
     * Here the game should clean up all the resources it uses and it owns, destroy all the remaining
     * components, and any other dependencies that it owns should also be destroyed here.
     */
    virtual void destroy() = 0;
};

/**
 * @brief This is the interface of game objects manager.
 *
 * A game objects manager is basically the container of the game objects
 * and the different components managers.
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
     * @brief This checks if the game manager contains the given component manager.
     *
     * @param manager ComponentManager pointer.
     *
     * @return `true` if the manager contains the given game object, else `false`.
     */
    virtual bool hasComponentManager(ComponentManager *manager) const = 0;

    /**
     * @brief This getter returns the list of all of the component managers.
     *
     * @return list of all component managers of the game objects contained in the current game objects manager.
     */
    virtual const std::unordered_set<ComponentManager *> managers() const = 0;
};
