#pragma once

#include <cstdint>
#include <vector>

struct IComponent;

/**
 * @brief This is the base interface of any component manager.
 */
struct IComponentManager
{
    virtual ~IComponentManager() = default;

    /**
     * @brief This method registers the given component as a component of the current component manager.
     *
     * @param componet The component to be registered.
     *
     * @return `true` if the component was registered successfully, else `false`.
     */
    virtual bool registerComponent(IComponent *componet) = 0;

    /**
     * @brief This method checks if the given component is being managed by the current manager.
     *
     * @param componet The component that will be checked.
     *
     * @return `true` if the component is being managed by the current manager, else `false`.
     */
    virtual bool hasComponent(IComponent *componet) const = 0;

    /**
     * @brief This method updates all the components managed by the current manager.
     *
     * @param deltatime Amount of time in ms since last frame.
     */
    virtual void updateComponents(uint32_t deltatime) = 0;

    /**
     * @brief This method destroys all the components managed by the current manager.
     */
    virtual void destroyComponents() = 0;
};

/**
 * @brief This is the interface of any component manager that manages output components.
 */
struct IOutputComponentManager : IComponentManager
{
    /**
     * @brief This method outputs the conents of the components managed by the current manager.
     */
    virtual void output() = 0;
};

struct IComponent
{
    ~IComponent() = default;
    virtual void update(uint32_t deltatime) = 0;
    virtual IComponentManager *manager() const = 0;
};
