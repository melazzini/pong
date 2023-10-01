#pragma once
#include <chrono>
#include <glm/glm.hpp>
#include <memory>

struct IRendererPrimitive;
struct Drawable;

struct ITicker
{
    [[nodiscard]] virtual std::chrono::milliseconds tick() = 0;
    virtual ~ITicker() = default;
};

/**
 * @brief This interface represents a renderer of drawables on the screen.
 */
struct IRenderer
{
    /**
     * @brief Used to render a drawable
     *
     * @param Drawable* drawable to be rendered
     */
    virtual void render(Drawable *drawable) = 0;

    /**
     * @brief Returns the renderer primitive, which be then be used internally
     *        for drawing the drawables.
     *
     * @return The instance of the renderer primitive.
     *
     * @warning A user of the facineroso api should not normally need to call this method.
     * @see Drawable
     */
    virtual IRendererPrimitive *primitive() = 0;

    virtual ~IRenderer() = default;
};

/**
 * @brief This interface represents a window.
 */
struct IWindow
{

    /**
     * @brief This method clears the window with a solid color.
     *
     * After you call this method, the window should have the given color
     * on its surface.
     *
     * @param color The color that will be used.
     */
    virtual void clear(glm::u8vec4 color) = 0;

    /**
     * @brief This method presents the new contents of the window.
     */
    virtual void present() = 0;

    virtual ~IWindow() = default;
};

