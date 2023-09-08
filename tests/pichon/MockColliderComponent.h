#pragma once

#include "GameObject.h"
#include "components/ColliderComponent.h"
struct DummyColliderShape
{
    bool collidesWith(const DummyColliderShape &other) const
    {
        return collides;
    }

    bool collides;
};

using ColliderComponentWithDummyShape = ColliderComponent<DummyColliderShape>;
using ColliderComponentManagerWithDummyShape = ColliderComponentManagerBase<DummyColliderShape>;

struct MockColliderComponentManagerBase : ColliderComponentManagerWithDummyShape
{
};
