#pragma once
#include "IPrimitives.h"

struct IRectangularDrawablePrimitive : IDrawablePrimitive
{
    glm::u8vec4 color;
    glm::ivec2 position;
    glm::ivec2 size;
};

struct ICircularDrawablePrimitive : IDrawablePrimitive
{
    glm::u8vec4 color;
    glm::ivec2 position;
    int32_t radius;
};

struct ITriangularDrawablePrimitive : IDrawablePrimitive
{
    glm::u8vec4 color;
    glm::ivec2 vertexAPosition;
    glm::ivec2 vertexBPosition;
    glm::ivec2 vertexCPosition;
};

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
