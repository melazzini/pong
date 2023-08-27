#pragma once
#include <glm/glm.hpp>
#include <memory>
struct Drawable;
struct IRendererPrimitive
{
};

struct IBackendContext
{
    virtual std::unique_ptr<IRendererPrimitive> rendererPrimitive() = 0;
};
/**
 * @brief This interface represents a renderer of drawables on the screen.
 */
struct IRenderer
{
    /**
     * @brief Used to render a drawable
     *
     * @description A game manager should use this method to render drawables.
     *
     * @param Drawable* drawable to be rendered
     */
    virtual void render(Drawable *drawable) = 0;

    virtual IRendererPrimitive *primitive() = 0;
};

struct IWindow
{
    virtual void clear(glm::u8vec4 color) = 0;

    virtual void present(IRenderer *) = 0;
};

/**
 * @brief This interface represents the primitive drawable
 * of the selected backend. For example, if you work with SDL
 * you should implement this interface to get the specific
 * drawable primitive that knows how to draw a kind of shapes
 * in SDL.
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
};
