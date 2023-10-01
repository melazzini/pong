#pragma once
#include "IPrimitives.h"

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
    virtual void setPosition(glm::uvec2 newPosition) = 0;

    /**
     * @brief Getter of the current positin of the drawable.
     *
     * @return The current position.
     */
    virtual glm::uvec2 position() const = 0;

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
struct IDrawablePrimitivesProvider
{
    virtual std::unique_ptr<IRectangularDrawablePrimitive> rectangularDrawablePrimitive() const = 0;
    virtual std::unique_ptr<ICircularDrawablePrimitive> circularDrawablePrimitive() const = 0;
    virtual std::unique_ptr<ITriangularDrawablePrimitive> triangularDrawablePrimitive() const = 0;
};

struct DrawablePrimitivesProviderSDL : IDrawablePrimitivesProvider
{
    std::unique_ptr<IRectangularDrawablePrimitive> rectangularDrawablePrimitive() const override;
    std::unique_ptr<ICircularDrawablePrimitive> circularDrawablePrimitive() const override;
    std::unique_ptr<ITriangularDrawablePrimitive> triangularDrawablePrimitive() const override;
};
