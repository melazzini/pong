#pragma once
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <memory>

enum class EventType
{
};
struct IEvent
{
    virtual EventType eventType() const = 0;
    ~IEvent() = default;
};

struct IListener
{
    virtual EventType eventType() const = 0;

    virtual void onEvent(const IEvent &event) = 0;
};

struct IEventManager
{
    virtual void registerListener(IListener *) = 0;
    [[nodiscard]] virtual bool isListenerRegistered(IListener *listener) const = 0;
    [[nodiscard]] virtual bool eventQueueHasEventType(EventType eventType) const = 0;
    [[nodiscard]] virtual bool isEventQueueEmpty() const = 0;
    virtual void pollEvents() = 0;
    virtual void enqueueEvent(std::unique_ptr<IEvent> event) = 0;
    virtual void dispatchEvents() = 0;
};

struct IEventManagerPrimitive
{
    virtual void pollEvents(IEventManager &) const = 0;
};
namespace backendContext
{
struct IEventManagerPrimitiveProvider
{
    virtual std::unique_ptr<IEventManagerPrimitive> provide() const = 0;
};
} // namespace backendContext
struct Drawable;
struct IRendererPrimitive
{
};
struct IWindowPrimitive
{
    virtual void clearWindow(glm::u8vec4 color) = 0;
    virtual void updateWindow() = 0;
    virtual ~IWindowPrimitive() = default;
};

struct IBackendContext
{
    virtual std::unique_ptr<IRendererPrimitive> rendererPrimitive() = 0;
    virtual std::unique_ptr<IWindowPrimitive> windowPrimitive() = 0;
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

    virtual void present() = 0;
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
