#pragma once
#include "components.h"
#include <algorithm>
#include <memory>
#include <vector>

struct GameObject
{
    template <typename ComponentT, typename... Args> ComponentT *addComponent(Args &&...args)
    {
        auto ptr = std::make_unique<ComponentT>(std::forward<Args>(args)...);
        auto refToComponent = ptr.get();
        m_components.push_back(std::move(ptr));
        return refToComponent;
    }
    template <typename ComponentT> [[nodiscard]] ComponentT *component()
    {
        for (auto &component : m_components)
        {
            if (auto componentPtr{dynamic_cast<ComponentT *>(component.get())}; componentPtr != nullptr)
            {
                return componentPtr;
            }
        }

        return nullptr;
    }

    template <typename ComponentT> bool hasComponent() const
    {
        for (auto &component : m_components)
        {
            if (auto componentPtr{dynamic_cast<ComponentT *>(component.get())}; componentPtr != nullptr)
            {
                return true;
            }
        }

        return false;
    }

    void updateComponents(float deltatime)
    {
        for (auto &component : m_components)
        {
            component->update(deltatime);
        }
    }

    virtual ~GameObject() = default;

  protected:
    std::vector<std::unique_ptr<Component>> m_components;
};
