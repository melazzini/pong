#include "DrawablePrimitivesFactory.h"
#include "RectangularShapePrimitiveSDL.h"
#include <memory>

std::unique_ptr<IRectangularDrawablePrimitive> DrawablePrimitivesFactory::rectangularDrawablePrimitive()
{
    return std::make_unique<RectangularShapePrimitiveSDL>();
}
