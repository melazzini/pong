#pragma once
#include "IPrimitives.h"

struct DrawablePrimitivesFactory
{
    static std::unique_ptr<IRectangularDrawablePrimitive> rectangularDrawablePrimitive();
    static std::unique_ptr<ICircularDrawablePrimitive> circularDrawablePrimitive();
    static std::unique_ptr<ITriangularDrawablePrimitive> triangularDrawablePrimitive();
};
