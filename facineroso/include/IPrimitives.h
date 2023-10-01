#pragma once
#include "EventUtils.h"
#include <glm/glm.hpp>
#include <memory>

/**
 * @brief This is the interface of a render primitive class.
 *
 * A render primitive class is an abstraction of the actual internal renderer object.
 * Whenever facineroso api renders content to the corresponding window, it uses the
 * renderer primitive.
 *
 * @note This is just an abstraction, and in some backends the concept of a renderer might
 *       be directly related to the window(the window itself is the actual renderer).
 *       Therefore, when you implement this interface you have to deal with these discrepancies
 *       and separate the responsibility of rendering drawables from the responsibility of managing the window.
 * @note Normally, there should be one renderer primitive.
 * @see IWindowPrimitive
 *
 * @warning This is not thought to be used by the user of the facineroso api, this abstraction is meant
 * to be used only internally by the api, and it should be implemented by the backend layer.
 *
 * @warning At the moment  this is interface has no methods because the ideas are not very clear yet.
 */
struct IRendererPrimitive
{
    virtual ~IRendererPrimitive() = default;
};

/**
 * @brief This is the interface of a window primitive class.
 *
 * A window primitive class, is an abstraction of the actual window object.
 * The window object, is the area on the screen where you display your graphics.
 *
 * @note The window is not thought to be used as a renderer, i.e. it is not its
 * responsibility to draw drawables onto the screen.
 *
 * @note Normally, there should be one window primitive.
 * @see IRendererPrimitive
 *
 * @warning This is not thought to be used by the user of the facineroso api, this abstraction is meant
 * to be used only internally by the api, and it should be implemented by the backend layer.
 */
struct IWindowPrimitive
{
    virtual ~IWindowPrimitive() = default;

    /**
     * @brief This method clears the window using a solid color.
     *
     * @param color The new color of the window.
     */
    virtual void clearWindow(glm::u8vec4 color) = 0;

    /**
     * @brief This method displays the new contents of the window.
     *
     * @note The contents that will be displayed have to be drawn internally by the IRendererPrimitive.
     */
    virtual void updateWindow() = 0;
};

/**
 * @brief This interface represents class that provides all the backend context elements, like the window primitive,
 * renderer, primitive, etc.
 *
 * A backend context is the collection of the objects that allow facineroso api to acomplish its rendering (graphics and
 * sound). But which are not the renderable objects themselves (e.g. a drawable shape).
 *
 * @note At the moment this means: the window primitive and the renderer primitive. But probably this will change.
 *       The ideas about this class are not very clear at the moment.
 */
struct IBackendContext
{
    virtual ~IBackendContext() = default;

    /**
     * @brief Provides the intance of the renderer primitive.
     *
     * @return Intance of the renderer primitive.
     */
    virtual std::unique_ptr<IRendererPrimitive> rendererPrimitive() = 0;

    /**
     * @brief Provides the intance of the window primitive.
     *
     * @return Intance of the window primitive.
     */
    virtual std::unique_ptr<IWindowPrimitive> windowPrimitive() = 0;
};

/**
 * @brief This interface represents the primitive drawable
 * of the selected backend.
 *
 * The backend should implement this interface to get the specific
 * drawable primitive that knows how to draw its corresponding shape (e.g. a rectangle, a circle, etc).
 *
 * @warning This is not thought to be used by the user of the facineroso api, this abstraction is meant
 * to be used only internally by the api, and it should be implemented by the backend layer.
 */
struct IDrawablePrimitive
{
    virtual ~IDrawablePrimitive() = default;

    /**
     * @brief This method should be called by the primitive
     * in order to paint its graphics using the chosen backend.
     *
     * @param renderer
     */
    virtual void paintWithRendererPrimitive(IRendererPrimitive *primitive) = 0;

    /**
     * @brief This method sets the backgroud color the drawable.
     *
     * @param newColor The given new color.
     */
    virtual void setBackgroundColor(glm::u8vec4 newColor) = 0;

    /**
     * @brief Getter of the current backgroud color of the drawable.
     *
     * @return The current background color.
     */
    virtual glm::u8vec4 backgroundColor() const = 0;
};

struct IEventManager;

/**
 * @brief This is the interface of an event manager primitive.
 *
 * An event manager primitive provides event polling and keyboard/mouse/other-controllers state checking
 * to the facineroso api.
 *
 * @warning This is not thought to be used by the user of the facineroso api, this abstraction is meant
 * to be used only internally by the api, and it should be implemented by the backend layer.
 */
struct IEventManagerPrimitive
{
    virtual ~IEventManagerPrimitive() = default;

    /**
     * @brief Poll the events into the event manager.
     *
     * After invoking this method, all the events that were in the event queue
     * will be polled into the given event manager.
     *
     * @param eventManager The actual event manager that will received the polled events.
     */
    virtual void pollEvents(IEventManager &eventManager) const = 0;

    /**
     * @brief This method checks whether the given key is pressed or not.
     *
     * @param key The key to be considered.
     *
     * @return `true` if the key is being pressed, else `false`.
     */
    virtual bool isKeyPressed(Keyboard key) const = 0;
};

/**
 * @brief This interface represents a rectangular drawable.
 */
struct IRectangularDrawablePrimitive : IDrawablePrimitive
{
    /**
     * @brief This method sets the position of the drawable.
     *
     * @param newPosition The given new position.
     */
    virtual void setPosition(glm::ivec2 newPosition) = 0;

    /**
     * @brief Getter of the current positin of the drawable.
     *
     * @return The current position.
     */
    virtual glm::ivec2 position() const = 0;

    /**
     * @brief Set a new size to the rectangular drawable.
     *
     * @param size Value of the new size.
     */
    virtual void setSize(glm::ivec2 size) = 0;

    /**
     * @brief Get the current size of the rectangular drawable.
     *
     * @return The value of the current size of the rectangular drawable.
     */
    virtual glm::ivec2 size() const = 0;
};

/**
 * @brief This interface represents a circular drawable.
 */
struct ICircularDrawablePrimitive : IDrawablePrimitive
{
    /**
     * @brief This method sets the position of the drawable.
     *
     * @param newPosition The given new position.
     */
    virtual void setPosition(glm::uvec2 newPosition) = 0;

    /**
     * @brief Getter of the current position of the drawable.
     *
     * @return The current position.
     */
    virtual glm::uvec2 position() const = 0;

    /**
     * @brief Get the current radius of the circular drawable.
     *
     * @return The value of the current radius of the circular drawable.
     */
    virtual int32_t radius() const = 0;

    /**
     * @brief Set a new radius to the circular drawable.
     *
     * @param newRadius Value of the new radius.
     */
    virtual void setRadius(int32_t newRadius) = 0;
};

/**
 * @brief This aggregate represents the position of the three vertices of a triangle.
 */
struct TriangleVerticesPosition
{
    glm::vec2 vertexA;
    glm::vec2 vertexB;
    glm::vec2 vertexC;
};

/**
 * @brief This interface represents a triagular drawable.
 */
struct ITriangularDrawablePrimitive : IDrawablePrimitive
{
    /**
     * @brief This method sets the position of the drawable.
     *
     * @param newPos The given new positions.
     */
    virtual void setVerticesPosition(TriangleVerticesPosition newPos) = 0;

    /**
     * @brief Getter of the current positions of the triangle vertices.
     *
     * @return The current positions.
     */
    virtual TriangleVerticesPosition triangleVerticesPosition() const = 0;
};

/**
 * @brief This interface represents an abstract factory, which provides all the different drawable primitives.
 */
struct IDrawablePrimitivesFactory
{
    virtual std::unique_ptr<IRectangularDrawablePrimitive> rectangularDrawablePrimitive() const = 0;
    virtual std::unique_ptr<ICircularDrawablePrimitive> circularDrawablePrimitive() const = 0;
    virtual std::unique_ptr<ITriangularDrawablePrimitive> triangularDrawablePrimitive() const = 0;
};
