#pragma once
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

    virtual ~IWindowPrimitive() = default;
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

    virtual ~IBackendContext() = default;
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
    /**
     * @brief This method should be called by the primitive
     * in order to paint its graphics using the chosen backend.
     *
     * @param renderer
     */
    virtual void paintWithRendererPrimitive(IRendererPrimitive *primitive) = 0;

    virtual ~IDrawablePrimitive() = default;
};
